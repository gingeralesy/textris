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
/** Converts x and y to array variable. */
static int xy_to_i(int x, int y);

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
    tetro.shape[2] = ch; // 1,0
    tetro.shape[5] = ch; // 1,1
    tetro.shape[9] = ch; // 1,2
    tetro.shape[13] = ch; // 1,3
    break;
  case TETRO_L:
    tetro.shape[2] = ch; // 1,0
    tetro.shape[5] = ch; // 1,1
    tetro.shape[9] = ch; // 1,2
    tetro.shape[3] = ch; // 0,2
    break;
  case TETRO_J:
    tetro.shape[2] = ch; // 1,0
    tetro.shape[5] = ch; // 1,1
    tetro.shape[9] = ch; // 1,2
    tetro.shape[0] = ch; // 0,0
    break;
  case TETRO_Z:
    tetro.shape[0] = ch; // 0,0
    tetro.shape[1] = ch; // 0,1
    tetro.shape[5] = ch; // 1,1
    tetro.shape[6] = ch; // 1,2
    break;
  case TETRO_S:
    tetro.shape[1] = ch; // 0,1
    tetro.shape[2] = ch; // 0,2
    tetro.shape[4] = ch; // 1,0
    tetro.shape[5] = ch; // 1,1
    break;
  case TETRO_O:
    tetro.shape[1] = ch; // 0,1
    tetro.shape[2] = ch; // 0,2
    tetro.shape[5] = ch; // 1,1
    tetro.shape[6] = ch; // 1,2
    break;
  case TETRO_T:
    tetro.shape[1] = ch; // 0,1
    tetro.shape[4] = ch; // 1,0
    tetro.shape[5] = ch; // 1,1
    tetro.shape[6] = ch; // 1,2
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
    int x,y;
    switch (_tetro.type)
    {
    case TETRO_I:
    case TETRO_L:
    case TETRO_J:
    case TETRO_Z:
    case TETRO_S:
    case TETRO_T:
      for (x = 0; x < 2; x++)
      {
        for (y = x; y < 3 - x; y++)
        {
          int temp = _tetro.shape[xy_to_i(x,y)];
          _tetro.shape[xy_to_i(x,y)] = _tetro.shape[xy_to_i(3-y,x)];
          _tetro.shape[xy_to_i(3-y,x)] = _tetro.shape[xy_to_i(3-x,3-y)];
          _tetro.shape[xy_to_i(3-x,3-y)] = _tetro.shape[xy_to_i(y,3-x)];
          _tetro.shape[xy_to_i(y,3-x)] = temp;
        }
      }
      break;
    case TETRO_O:
    default:
      break;
    }
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
    int x,y;
    switch (_tetro.type)
    {
    case TETRO_I:
    case TETRO_L:
    case TETRO_J:
    case TETRO_Z:
    case TETRO_S:
    case TETRO_T:
      for (x = 0; x < 2; x++)
      {
        for (y = x; y < 3 - x; y++)
        {
          int temp = _tetro.shape[xy_to_i(x,y)];
          _tetro.shape[xy_to_i(x,y)] = _tetro.shape[xy_to_i(y,3-x)];
          _tetro.shape[xy_to_i(y,3-x)] = _tetro.shape[xy_to_i(3-x,3-y)];
          _tetro.shape[xy_to_i(3-x,3-y)] = _tetro.shape[xy_to_i(3-y,x)];
          _tetro.shape[xy_to_i(3-y,x)] = temp;
        }
      }
      break;
    case TETRO_O:
    default:
      break;
    }
  }
}

int xy_to_i(int x, int y)
{
  return (x + (y * 4));
}
