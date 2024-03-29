#include "game.h"
#include "lib.h"
#include "pong.h"
#include "window.h"
#include <unistd.h>

int main() {
  SDL_Window *window = nullptr;
  SDL_Surface *surface = nullptr;
  initSDL(window, surface);
  Point<double> center = getCenter(surface->w, surface->h);
  // SDL_Log("center: %f, %f", center.x, center.y);
  Player *playerOne = new Player(1);
  Ball *ball = new Ball(center.x, center.y);

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        quit = true;
      } else if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
        quit = true;
      }
      getKey(e, playerOne);
    }
  }
  cleanSDL(window);
}
