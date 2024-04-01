#include "window.hpp"
#include "lib.hpp"
#include <SDL.h>

void initSDL(SDL_Window *&window, SDL_Renderer *&renderer) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    EXIT_FAILURE;
  }
  initWindow(window, DIM_X, DIM_Y);
  initRender(window, renderer);
}

void initWindow(SDL_Window *&window, int width, int height) {
  window =
      SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    std::cout << "Could not create window " << std::endl;
    EXIT_FAILURE;
  }
}

void initRender(SDL_Window *&window, SDL_Renderer *&renderer) {
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cout << "Could not initialize renderer! SDL_ERROR: " << SDL_GetError()
              << std::endl;
    EXIT_FAILURE;
  }
}

void cleanSDL(SDL_Window *window, SDL_Renderer *renderer) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

Point<double> getCenter(int w, int h) {
  Point<double> point;
  point.x = w / 2;
  point.y = h / 2;
  return point;
}
