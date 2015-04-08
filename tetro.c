#include <stdio.h>
#include <stdlib.h>

#include "tetro.h"

// Tetro data and functions

// Constants

const char TetroCharacters[] = { '\0', 'I', 'L', 'J', 'Z', 'S', 'O', 'T' };

// Private headers

/** Copies shape from in to out. */
static void tetro_shape_copy(char from[4][4], char to[4][4]);
/** Sets all values in shape to null character. */
static void tetro_shape_null(char shape[4][4]);

// Implementations
// Private

static void tetro_shape_copy(char from[4][4], char to[4][4])
{
  int i,j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      to[i][j] = from[i][j];
}

static void tetro_shape_null(char shape[4][4])
{
  int i,j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      shape[i][j] = '\0';
}

// Public

Tetro * tetro_init(TetroType tetro_type)
{
  Tetro *tetro = (Tetro *)malloc(sizeof(Tetro));
  char ch = TetroCharacters[tetro_type];

  tetro_shape_null(tetro->shape);

  switch (tetro_type)
  {
  case TETRO_I:
    tetro->shape[1][0] = ch;
    tetro->shape[1][1] = ch;
    tetro->shape[1][2] = ch;
    tetro->shape[1][3] = ch;
    break;
  case TETRO_L:
    tetro->shape[1][0] = ch;
    tetro->shape[1][1] = ch;
    tetro->shape[1][2] = ch;
    tetro->shape[0][2] = ch;
    break;
  case TETRO_J:
    tetro->shape[1][0] = ch;
    tetro->shape[1][1] = ch;
    tetro->shape[1][2] = ch;
    tetro->shape[0][0] = ch;
    break;
  case TETRO_Z:
    tetro->shape[0][0] = ch;
    tetro->shape[0][1] = ch;
    tetro->shape[1][1] = ch;
    tetro->shape[1][2] = ch;
    break;
  case TETRO_S:
    tetro->shape[0][1] = ch;
    tetro->shape[0][2] = ch;
    tetro->shape[1][0] = ch;
    tetro->shape[1][1] = ch;
    break;
  case TETRO_O:
    tetro->shape[0][1] = ch;
    tetro->shape[0][2] = ch;
    tetro->shape[1][1] = ch;
    tetro->shape[1][2] = ch;
    break;
  case TETRO_T:
    tetro->shape[0][1] = ch;
    tetro->shape[1][0] = ch;
    tetro->shape[1][1] = ch;
    tetro->shape[1][2] = ch;
    break;
  default:
    free(tetro);
    return (void *)0;
  }
  tetro->type = tetro_type;
  tetro->ch = ch;
  tetro->orientation = TETRO_UP;

  return tetro;
}

void tetro_turn_clockwise(Tetro *tetro)
{
  int i,j;
  char old_shape[4][4];
  char new_shape[4][4];

  tetro_shape_copy(tetro->shape,old_shape);
  switch (tetro->type)
  {
  case TETRO_I:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        new_shape[i][j] = old_shape[3-j][i];
    break;
  case TETRO_L:
  case TETRO_J:
  case TETRO_Z:
  case TETRO_S:
  case TETRO_T:
    tetro_shape_null(new_shape);
    for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
        new_shape[i][j] = old_shape[2-j][i];
    break;
    break;
  case TETRO_O:
  default:
    tetro_shape_copy(old_shape,new_shape);
    break;
  }
  tetro->orientation += 1;
  if (tetro->orientation >= TETRO_ORIENTATION_MAX)
    tetro->orientation = TETRO_UP;
  tetro_shape_copy(new_shape,tetro->shape);
}

void tetro_turn_counter_clockwise(Tetro *tetro)
{
  int i,j;
  char old_shape[4][4];
  char new_shape[4][4];

  tetro_shape_copy(tetro->shape,old_shape);
  switch (tetro->type)
  {
  case TETRO_I:
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++)
        new_shape[i][j] = old_shape[j][3-i];
    break;
  case TETRO_L:
  case TETRO_J:
  case TETRO_Z:
  case TETRO_S:
  case TETRO_T:
    tetro_shape_null(new_shape);
    for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
        new_shape[i][j] = old_shape[j][2-i];
    break;
    break;
  case TETRO_O:
  default:
    tetro_shape_copy(old_shape,new_shape);
    break;
  }
  tetro->orientation -= 1;
  if (tetro->orientation < TETRO_UP)
    tetro->orientation = TETRO_LEFT;
  tetro_shape_copy(new_shape,tetro->shape);
}
