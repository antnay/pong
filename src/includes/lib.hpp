#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>

#define SQUARE 500
#define DIM_X SQUARE
#define DIM_Y SQUARE
#define SET_FPS 144
#define UP_ONE SDL_SCANCODE_W
#define DOWN_ONE SDL_SCANCODE_S
#define UP_TWO SDL_SCANCODE_I
#define DOWN_TWO SDL_SCANCODE_K
#define MAXANGLE (5 * M_PI / 12) // 75 degree
#define BALL_VELOCITY 2
#define PLAYER_VELOCITY 6
#define PADDLEWIDTH (DIM_X * .01)
#define PADDLEHEIGHT (DIM_Y * .18)
#define BALLHEIGHT (DIM_X * .02)
#define CENTER (DIM_X / 2 - (PADDLEWIDTH / 2))

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
