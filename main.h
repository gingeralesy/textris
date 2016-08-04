#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "tetro.h"

typedef struct Entity_st {
  Tetro * tetro;
  int x;
  int y;
} Entity;

#endif // MAIN_H_INCLUDED
