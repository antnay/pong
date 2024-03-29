#include "window.h"
#include "/opt/homebrew/opt/sdl2/include/SDL2/SDL.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

void initSDL(SDL_Window *&window, SDL_Surface *surface) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    EXIT_FAILURE;
  }
  initWindow(window, 500, 500);

  // SDL_Renderer *renderer =
  //     SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  // if (renderer == NULL) {
  //   std::cout << "Could not initalize renderer! SDL_ERROR: " <<
  //   SDL_GetError()
  //             << std::endl;
  //   EXIT_FAILURE;
  // }
  // std::cout << "Renderer created" << std::endl;

  for (int i = 0; i < 5; ++i) {
    SDL_PumpEvents();
  }

  surface = SDL_GetWindowSurface(window);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window);

}

void initWindow(SDL_Window *&window, int width, int height) {
  window =
      SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    std::cout << "Could not create window " << std::endl;
    EXIT_FAILURE;
  }
  std::cout << "Window created" << std::endl;
}

void cleanSDL(SDL_Window *window) {
  SDL_DestroyWindow(window);
  SDL_Quit();
}
