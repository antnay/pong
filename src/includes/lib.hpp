#ifndef _LIB_HPP_
#define _LIB_HPP_
#include <SDL.h>
// #include "/opt/homebrew/opt/sdl2/include/SDL2/SDL.h"
// #include <SDL_ttf.h>
#include <unistd.h>

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

#define SQUARE 500
#define DIM_X SQUARE
#define DIM_Y SQUARE

template <class t>
struct Point {
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

std::vector<SDL_Point> PixelizeCircle(SDL_Point center, int radius);
std::vector<SDL_Vertex> triangleFanCirc(int x, int y, int radius, int segments);
int roundUpToMultipleOfEight(int v);
int circleDims();
Point<double> circlePos();
void GenerateCircle(std::vector<SDL_Vertex> &outCircleVertices,
                    size_t vertexCount, int radius,
                    std::vector<int> &outIndices);
#endif
