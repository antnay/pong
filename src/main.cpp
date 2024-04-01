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
  gameRender(renderer, playerOne, playerTwo, ball);
  int frameCount, timerFPS, lastFrame, fps;
  static int lastTime = 0;
  serveBall(renderer, ball);

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
    quit = getKey(e, quit, ball);
    movePlayerOne(playerOne);
    movePlayerTwo(playerTwo);

    gameRender(renderer, playerOne, playerTwo, ball);
    // playerOne->status();
    // playerTwo->status();
    ball->status();
  }
  cleanSDL(window, renderer);
}
