#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <math.h>

#include "utils.h"

#include "main.h"

// Static interface headers
/** Closes the program. */
static void close();
/** Initializes the program. */
static void init();
/** Update loop. */
static void loop();
/** Paint call */
static void paint();
/** Update call. */
static void update();

// Variables
Entity * entity;

// Public interface implementations
// -- Entity
Entity * entity_init()
{
  Entity *e = malloc(sizeof(Entity));
  e->tetro = tetro_init(TETRO_S);
  e->x = 10;
  e->y = 5;
  return e;
}

void entity_free(Entity *e)
{
  if (e)
  {
    if (e->tetro)
      tetro_free(e->tetro);
    e->tetro = 0;
    free(e);
  }
}

// Static interface implementations
static void close()
{
  entity_free(entity);
  endwin();
}

static void init()
{
  initscr();

  if (has_colors() == FALSE)
  {
    endwin();
    printf("Does not support colours!\n");
    exit(EXIT_FAILURE);
  }

  start_color();
  raw();
  keypad(stdscr,TRUE);
  noecho();
  timeout(16);
  curs_set(0);

  init_color(TETRO_I,1000,0,0);
  init_color(TETRO_L,750,250,0);
  init_color(TETRO_J,0,0,1000);
  init_color(TETRO_Z,0,500,500);
  init_color(TETRO_S,0,1000,0);
  init_color(TETRO_O,500,500,0);
  init_color(TETRO_T,500,0,500);

  init_pair(TETRO_I,TETRO_I,TETRO_I);
  init_pair(TETRO_L,TETRO_L,TETRO_L);
  init_pair(TETRO_J,TETRO_J,TETRO_J);
  init_pair(TETRO_Z,TETRO_Z,TETRO_Z);
  init_pair(TETRO_S,TETRO_S,TETRO_S);
  init_pair(TETRO_O,TETRO_O,TETRO_O);
  init_pair(TETRO_T,TETRO_T,TETRO_T);

  entity = entity_init();
}

static void loop()
{
  static long int tick_length = (1000 / 30); // milliseconds
  long int last_update = 0;
  int input = ERR;
  int ch = ERR;

  do
  {
    struct timespec spec;
    long int time_now;
    clock_gettime(CLOCK_REALTIME, &spec);
    time_now = lround(spec.tv_nsec / 1000000.0);

    ch = getch();
    if (ch != ERR)
      input = ch;

    if (tick_length <= time_now - last_update)
    {
      last_update = time_now;
      
      if (input != ERR)
      {
        update(input);
        input = ERR;
      }
      paint();
    }
  } while (ch != 'q');
}

static void paint()
{
  int x,y;
  clear();
  
  attron(COLOR_PAIR(entity->tetro->type));
  for (x = 0; x < 4; x++)
  {
    for (y = 0; y < 4; y++)
    {
      if (entity->tetro->shape[xy_to_i(x,y)] != '\0')
        mvaddch(entity->y + y,entity->x + x,' ' | A_BOLD);
    }
  }
  attroff(COLOR_PAIR(entity->tetro->type));
  
  refresh();
}

static void update(int input)
{
  TetroType new_type;
  switch (input)
  {
  case KEY_UP:
    tetro_turn_clockwise(&entity->tetro);
    break;
  case KEY_LEFT:
    entity->x -= 1;
    break;
  case KEY_RIGHT:
    entity->x += 1;
    break;
  case '1':
    new_type = entity->tetro->type + 1;
    if (new_type == TETRO_TYPE_MAX)
      new_type = TETRO_I;
    tetro_free(entity->tetro);
    entity->tetro = tetro_init(new_type);
    break;
  default:
    break;
  }
}

// Public interface
/** Runs the program. */
int main(int argc, char * argv[])
{
  init();
  loop();
  close();
  return EXIT_SUCCESS;
}
