#ifndef _LIB_H_
#define _LIB_H_
#include "/opt/homebrew/opt/sdl2/include/SDL2/SDL.h"

template <class t> struct Point {
  t x;
  t y;
};

typedef struct Rectangle {
  double w;
  double h;
} rectangle;

typedef struct Circle {
  double r;
} circle;
#endif
