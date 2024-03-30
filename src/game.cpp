#include "../headers/game.hpp"
#include "../headers/pong.hpp"

bool getKey(SDL_Event e, bool quit, Player *&player, Ball *&ball) {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      quit = true;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      quit = true;
    } else if (e.key.keysym.scancode == SDL_SCANCODE_SPACE) {
      quit = true;
    } else if (e.key.keysym.scancode == SDL_SCANCODE_O) {
      ball->reset();
    }
    if (e.type == SDL_KEYDOWN) {
      if (currentKeyStates[SDL_SCANCODE_W])
        switch (currentKeyStates[SDL_SCANCODE_W]) {
        case 1:
          player->posUp();
          // SDL_Log("Player pos: %d up", player->getRect()->y);
        }
      switch (currentKeyStates[SDL_SCANCODE_S]) {
      case 1:
        player->posDown();
        // SDL_Log("Player pos: %d down", player->getRect()->y);
      }
      // SDL_Log("Player One Pos: %f", player->getPos());
    }
  }
  return quit;
}

void gameRender(SDL_Renderer *&renderer, Player *playerOne, Player *playerTwo,
                Ball *ball) {
  SDL_SetRenderDrawColor(renderer, 32, 32, 37, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 225, 150, 107, 255);
  SDL_RenderFillRect(renderer, playerOne->getRect());
  SDL_RenderFillRect(renderer, playerTwo->getRect());
  SDL_RenderFillRect(renderer, ball->getRect());
  SDL_RenderPresent(renderer);
}

void serveBall(SDL_Renderer *renderer, Ball *&ball) { ball->setVel(5, 0); }

void moveBall(Ball *&ball, Player *playerOne, Player *playerTwo, double dt) {
  SDL_Rect *pos = ball->getRect();
  Point<double> vel = ball->getVel();
  collision(ball, playerOne, playerTwo);
  ball->setPos(pos->x += vel.x, pos->y += vel.y);
}

void collision(Ball *&ball, Player *playerOne, Player *playerTwo) {
  SDL_Rect *ballRec = ball->getRect();
  Point<double> vel = ball->getVel();
  if (SDL_HasIntersection(ballRec, playerOne->getRect())) {
    ball->setVel(-1 * vel.x, vel.y);
    // SDL_Log("switching 1: (%d, %d)", ball->getRect()->x, ball->getRect()->y);
  }
  if (SDL_HasIntersection(ballRec, playerTwo->getRect())) {
    ball->setVel(-1 * vel.x, vel.y);
    SDL_Log("switching 2: (%d, %d)", ball->getRect()->x, ball->getRect()->y);
  }

  if (ballRec->y < (0 + (ballRec->h / 2)))
    ball->setVel(vel.x, -1 * vel.y);
  if (ballRec->y > (DIM_Y - (ballRec->h / 2)))
    ball->setVel(vel.x, -1 * vel.y);
}
