#include "game.h"
#include <iostream>

void getKey(SDL_Event e, Player *&player) {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  if (e.type == SDL_KEYDOWN) {
    if (currentKeyStates[SDL_SCANCODE_W])
      switch (currentKeyStates[SDL_SCANCODE_W]) {
      case 1:
        player->posUp();
      }
    switch (currentKeyStates[SDL_SCANCODE_S]) {
    case 1:
      player->posDown();
    }
    std::cout << player->getPos() << std::endl;
    // SDL_Log("Player One Pos: %f", player->getPos());
  }
}
