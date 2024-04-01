#include "game.hpp"
#include "lib.hpp"
#include "pong.hpp"
#include "window.hpp"
#include <unistd.h>

int main() {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  initSDL(window, renderer);
  // SDL_Log("center: %f, %f", center.x, center.y);
  Player *playerOne = new Player(1);
  Player *playerTwo = new Player(2);
  Ball *ball = new Ball();
  int frameCount, timerFPS, lastFrame, fps;
  static int lastTime = 0;
  serveBall(renderer, ball);
  SDL_Rect middleRect;
  middleRect.h = DIM_Y * .8;
  middleRect.w = DIM_X * .01;
  middleRect.x = 250 - middleRect.w / 2;
  middleRect.y = 250 - middleRect.h / 2;
  gameRender(renderer, playerOne, playerTwo, ball, &middleRect);

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    lastFrame = SDL_GetTicks();
    if (lastFrame >= (lastTime + 1000)) {
      lastTime = lastFrame;
      fps = frameCount;
      frameCount = 0;
    }

    // physics and logic before render
    moveBall(ball, playerOne, playerTwo);
    score(ball, playerOne, playerTwo);
    quit = getKey(e, quit, ball);
    movePlayerOne(playerOne);
    movePlayerTwo(playerTwo);
    gameRender(renderer, playerOne, playerTwo, ball, &middleRect);
    // playerOne->status();
    // playerTwo->status();
    ball->status();
  }
  cleanSDL(window, renderer);
}
