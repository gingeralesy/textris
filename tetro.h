#ifndef TETRO_H_INCLUDED
#define TETRO_H_INCLUDED

// Enums

enum TetroType_e
{
  TETRO_I = 1,
  TETRO_L,
  TETRO_J,
  TETRO_Z,
  TETRO_S,
  TETRO_O,
  TETRO_T,
  TETRO_TYPE_MAX
};
typedef short int TetroType;

enum TetroOrientantion_e
{
  TETRO_UP = 1,
  TETRO_RIGHT,
  TETRO_DOWN,
  TETRO_LEFT,
  TETRO_ORIENTATION_MAX
};
typedef short int TetroOrientation;

// Constants

extern const char TetroCharacters[];

// Structs

struct Tetro_st
{
  TetroType type;
  char ch;
  char shape[16];
  TetroOrientation orientation;
};
typedef struct Tetro_st Tetro;

// Headers

/** Initializes a tetro. */
Tetro tetro_init(TetroType tetro_type);
/** Turns the tetro clockwise. */
void tetro_turn_clockwise(Tetro *tetro);
/** Turns the tetro counter-clockwise. */
void tetro_turn_counter_clockwise(Tetro *tetro);

#endif // TETRO_H_INCLUDED
