#include "../headers/game.hpp"
#include "../headers/lib.hpp"
#include "../headers/pong.hpp"
#include "../headers/window.hpp"
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
    double dt = lastFrame / 1000;

    // physics and logic before render
    moveBall(ball, playerOne, playerTwo, dt);
    quit = getKey(e, quit, playerOne, ball);

    gameRender(renderer, playerOne, playerTwo, ball);
    // playerOne->status();
    // playerTwo->status();
    ball->status();
  }
  cleanSDL(window, renderer);
}
