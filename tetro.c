#include <stdio.h>
#include <stdlib.h>

#include "tetro.h"

// Tetro data and functions

// Constants

const char TetroCharacters[] = { '\0', 'I', 'L', 'J', 'Z', 'S', 'O', 'T' };

// Private headers

/** Copies shape from in to out. */
static void tetro_shape_copy(char from[16],Tetro *tetro);
/** Sets all values in shape to null character. */
static void tetro_shape_null(Tetro *tetro);

// Implementations
// Private

static void tetro_shape_copy(char from[16],Tetro *tetro)
{
  int i;
  Tetro _tetro = *tetro;
  for (i = 0; i < 16; i++)
    _tetro.shape[i] = from[i];
}

static void tetro_shape_null(Tetro *tetro)
{
  int i;
  Tetro _tetro = *tetro;
  for (i = 0; i < 16; i++)
    _tetro.shape[i] = '\0';
}

// Public

Tetro tetro_init(TetroType tetro_type)
{
  Tetro tetro;
  char ch = TetroCharacters[tetro_type];

  tetro_shape_null(&tetro);

  switch (tetro_type)
  {
  case TETRO_I:
    tetro.shape[1][0] = ch; // 1,0
    tetro.shape[1][1] = ch;
    tetro.shape[1][2] = ch;
    tetro.shape[1][3] = ch;
    break;
  case TETRO_L:
    tetro.shape[1][0] = ch;
    tetro.shape[1][1] = ch;
    tetro.shape[1][2] = ch;
    tetro.shape[0][2] = ch;
    break;
  case TETRO_J:
    tetro.shape[1][0] = ch;
    tetro.shape[1][1] = ch;
    tetro.shape[1][2] = ch;
    tetro.shape[0][0] = ch;
    break;
  case TETRO_Z:
    tetro.shape[0][0] = ch;
    tetro.shape[0][1] = ch;
    tetro.shape[1][1] = ch;
    tetro.shape[1][2] = ch;
    break;
  case TETRO_S:
    tetro.shape[0][1] = ch;
    tetro.shape[0][2] = ch;
    tetro.shape[1][0] = ch;
    tetro.shape[1][1] = ch;
    break;
  case TETRO_O:
    tetro.shape[0][1] = ch;
    tetro.shape[0][2] = ch;
    tetro.shape[1][1] = ch;
    tetro.shape[1][2] = ch;
    break;
  case TETRO_T:
    tetro.shape[0][1] = ch;
    tetro.shape[1][0] = ch;
    tetro.shape[1][1] = ch;
    tetro.shape[1][2] = ch;
    break;
  default:
    exit(EXIT_FAILURE);
  }
  tetro.type = tetro_type;
  tetro.ch = ch;
  tetro.orientation = TETRO_UP;

  return tetro;
}

void tetro_turn_clockwise(Tetro *tetro)
{
  Tetro _tetro = *tetro;
  _tetro.orientation += 1;
  if (_tetro.orientation >= TETRO_ORIENTATION_MAX)
    _tetro.orientation = TETRO_UP;

  if (_tetro.type > 0 && _tetro.type < TETRO_TYPE_MAX &&
      _tetro.type != TETRO_O)
  {
    int i,j;
    char old_shape[4][4];
    char new_shape[4][4];

    tetro_shape_copy(_tetro.shape,&old_shape);
    switch (_tetro.type)
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
      tetro_shape_null(&_tetro);
      for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
          new_shape[i][j] = old_shape[2-j][i];
      break;
      break;
    case TETRO_O:
    default:
      tetro_shape_copy(old_shape,&new_shape);
      break;
    }
    tetro_shape_copy(new_shape,&_tetro.shape);
  }
}

void tetro_turn_counter_clockwise(Tetro *tetro)
{
  Tetro _tetro = *tetro;
  _tetro.orientation -= 1;
  if (_tetro.orientation < TETRO_UP)
    _tetro.orientation = TETRO_LEFT;

  if (_tetro.type > 0 && _tetro.type < TETRO_TYPE_MAX &&
      _tetro.type != TETRO_O)
  {
    int i,j;
    char old_shape[4][4];
    char new_shape[4][4];

    tetro_shape_copy(_tetro.shape,&old_shape);
    switch (_tetro.type)
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
      tetro_shape_null(&_tetro);
      for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
          new_shape[i][j] = old_shape[j][2-i];
      break;
      break;
    case TETRO_O:
    default:
      break;
    }
    tetro_shape_copy(new_shape,&_tetro);
  }
}
