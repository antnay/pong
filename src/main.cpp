#include "game.hpp"
#include "lib.hpp"
#include "pong.hpp"
#include "window.hpp"
#include <SDL_log.h>
#include <unistd.h>

// TODO: refactor macros
// TODO: mess with speeds and make it easily adjustable with macros
// TODO: render score
// TODO: AI

int main() {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  initSDL(window, renderer);
  Player *playerOne = new Player(1);
  Player *playerTwo = new Player(2);
  Ball *ball = new Ball();
  SDL_Rect middleRect;
  middleRect.h = DIM_Y * .8;
  middleRect.w = DIM_X * .01;
  middleRect.x = 250 - middleRect.w / 2;
  middleRect.y = 250 - middleRect.h / 2;
  gameRender(renderer, playerOne, playerTwo, ball, &middleRect);
  serveBall(renderer, ball);

  SDL_Event e;
  bool quit = false;
  Uint32 lastFrame, frameTime, startFrame;
  const Uint32 FPS = 1000 / SET_FPS;
  while (!quit) {
    startFrame = SDL_GetTicks();

    moveBall(ball, playerOne, playerTwo);
    score(ball, playerOne, playerTwo);
    quit = getKey(e, quit, ball);
    movePlayerOne(playerOne);
    movePlayerTwo(playerTwo);
    gameRender(renderer, playerOne, playerTwo, ball, &middleRect);
    ball->status();

    lastFrame = SDL_GetTicks();
    frameTime = lastFrame - startFrame;
    if (frameTime < FPS) {
      SDL_Delay(FPS - frameTime);
    }
  }
  cleanSDL(window, renderer);
}
