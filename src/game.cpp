#include "game.hpp"

#include "lib.hpp"
#include "pong.hpp"
#include <SDL_rect.h>
#include <SDL_render.h>

#define UP_ONE SDL_SCANCODE_W
#define DOWN_ONE SDL_SCANCODE_S
#define UP_TWO SDL_SCANCODE_I
#define DOWN_TWO SDL_SCANCODE_K
#define MAXANGLE (5 * M_PI / 12) // 75 degree
#define BALLVEL 5

double halfRect = PADDLEHEIGHT / 2;
double halfBall = BALLHEIGHT / 2;
double maxAngle = 5 * M_PI / 12;

bool getKey(SDL_Event &e, bool quit, Ball *&ball) {
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
  }
  return quit;
}

void score (Ball *ball, Player *playerOne, Player *playerTwo) {
  if (ball->getPos().x <= 0) {
    playerTwo->incrPoint();
    ball->reset();
  }
  if (ball->getPos().x >= DIM_X) {
    playerOne->incrPoint();
    ball->reset();
  }
}

void movePlayerOne(Player *&player) {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  if (currentKeyStates[UP_ONE]) {
    if (player->getY() + halfRect >= 0)
      player->posUp();
  }
  if (currentKeyStates[DOWN_ONE]) {
    if (player->getY() + PADDLEHEIGHT <= DIM_Y)
      player->posDown();
  }
}

void movePlayerTwo(Player *&player) {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  if (currentKeyStates[UP_TWO]) {
    if (player->getY() + halfRect >= 0)
      player->posUp();
  }
  if (currentKeyStates[DOWN_TWO]) {
    if (player->getY() + PADDLEHEIGHT <= DIM_Y)
      player->posDown();
  }
}

void gameRender(SDL_Renderer *&renderer, Player *playerOne, Player *playerTwo,
                Ball *ball, SDL_Rect *centerRect) {
  SDL_SetRenderDrawColor(renderer, 32, 32, 37, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 225, 150, 107, 255);
  SDL_RenderFillRect(renderer, playerOne->getRect());
  SDL_RenderFillRect(renderer, playerTwo->getRect());
  SDL_RenderFillRect(renderer, ball->getRect());
  SDL_SetRenderDrawColor(renderer, 225, 150, 107, 50);
  SDL_RenderFillRect(renderer, centerRect);
  SDL_RenderPresent(renderer);
}

void serveBall(SDL_Renderer *renderer, Ball *&ball) {
  ball->reset();
  // ball->setVel(5, 0);
}

void moveBall(Ball *&ball, Player *playerOne, Player *playerTwo) {
  SDL_Rect *pos = ball->getRect();
  Point<double> vel = ball->getVel();

  ball->setPos(pos->x += vel.x, pos->y += vel.y);

  collision(ball, playerOne, playerTwo);
}

void collision(Ball *&ball, Player *playerOne, Player *playerTwo) {
  SDL_Rect *ballRec = ball->getRect();
  Point<double> vel = ball->getVel();

  if (SDL_HasIntersection(ballRec, playerOne->getRect())) {
    int intersect =
        (playerOne->getY() + halfRect) - (ball->getPos().y + halfBall);
    double normIntersect = intersect / halfRect;
    double angle = normIntersect * maxAngle;
    ball->setVel(BALLVEL * cos(angle), BALLVEL * -sin(angle));
  }

  if (SDL_HasIntersection(ballRec, playerTwo->getRect())) {
    int intersect =
        (playerTwo->getY() + halfRect) - (ball->getPos().y + halfBall);
    double normIntersect = intersect / halfRect;
    double angle = normIntersect * maxAngle;
    ball->setVel(-BALLVEL * cos(angle), BALLVEL * -sin(angle));
  }

  if (ballRec->y < (0 - (ballRec->h / 2))) {
    ball->setVel(vel.x, -1 * vel.y);
    SDL_Log("switched 1");
  }
  if (ballRec->y >= (DIM_Y - (ballRec->h / 2))) {
    ball->setVel(vel.x, -1 * vel.y);
    SDL_Log("switched 2");
  }
}
