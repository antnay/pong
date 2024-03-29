// #include "pong.h"
#include "game.h"
#include "pong.h"
#include "window.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <unistd.h>

int main() {
  SDL_Window *window = nullptr;
  SDL_Surface *surface = nullptr;
  initSDL(window, surface);
  Player PlayerOne(1);

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
      if (e.type == SDL_KEYDOWN) {
        if (currentKeyStates[SDL_SCANCODE_W])
          switch (currentKeyStates[SDL_SCANCODE_W]) {
          case 1:
            PlayerOne.posUp();
            std::cout << "UP" << std::endl;
          }
        switch (currentKeyStates[SDL_SCANCODE_S]) {
        case 1:
          PlayerOne.posDown();
          std::cout << "DOWN" << std::endl;
        }
        std::cout << PlayerOne.getPos() << std::endl;
      }
    }
  }
  cleanSDL(window);
}
