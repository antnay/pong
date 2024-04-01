#include "game.hpp"

#include "pong.hpp"

#define UP_ONE SDL_SCANCODE_W
#define DOWN_ONE SDL_SCANCODE_S
#define UP_TWO SDL_SCANCODE_I
#define DOWN_TWO SDL_SCANCODE_K
#define MAXANGLE (5 * M_PI / 12) // 75 degree

double halfRect = RECTHEIGHT / 2;
double halfBall = BALLHEIGHT / 2;

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

void movePlayerOne(Player *&player) {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  if (currentKeyStates[UP_ONE])
    player->posUp();
  if (currentKeyStates[DOWN_ONE])
    player->posDown();
}

void movePlayerTwo(Player *&player) {
  const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
  if (currentKeyStates[UP_TWO])
    player->posUp();
  if (currentKeyStates[DOWN_TWO])
    player->posDown();
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

void serveBall(SDL_Renderer *renderer, Ball *&ball) {
  ball->reset();
  // ball->setVel(5, 0);
}

void moveBall(Ball *&ball, Player *playerOne, Player *playerTwo) {
  SDL_Rect *pos = ball->getRect();
  Point<double> vel = ball->getVel();

  ball->setPos(pos->x += vel.x, pos->y += vel.y);

  // collision(ball, playerOne, playerTwo);
  if (SDL_HasIntersection(ball->getRect(), playerOne->getRect())) {
    // ball->setVel(-1 * vel.x, vel.y);
  }

  if (SDL_HasIntersection(ball->getRect(), playerTwo->getRect())) {
    // ball->setVel(-1 * vel.x, vel.y);
  }

  if (pos->y < (0 + (pos->h / 2)))
    ball->setVel(vel.x, -1 * vel.y);
  if (pos->y > (DIM_Y - (pos->h / 2)))
    ball->setVel(vel.x, -1 * vel.y);
}

void collision(Ball *&ball, Player *playerOne, Player *playerTwo) {
  SDL_Rect *ballRec = ball->getRect();
  Point<double> vel = ball->getVel();

  if (SDL_HasIntersection(ballRec, playerOne->getRect())) {
    int intersect =
        (playerOne->getY() + halfRect) - (ball->getPos().y + halfBall);
    double normIntersect = intersect / halfRect;
    double angle = normIntersect * MAXANGLE;
    ball->setVel(vel.x * cos(angle), vel.y * -sin(angle));
    // ball->setVel(-1 * vel.x, vel.y);
  }

  if (SDL_HasIntersection(ballRec, playerTwo->getRect())) {
    double intersect = (playerOne->getY() + (playerOne->getRect()->h / 2)) -
                       (ball->getPos().y + ball->getRect()->h / 2);
    double normIntersect = intersect / (playerOne->getRect()->h / 2);
    double angle = normIntersect * (5 * M_PI / 12);
    // ball->setVel(-vel.x * cos(angle), vel.y * -sin(angle));
    double xVel = (5 * cos(angle));
    double yVel = 5 * -sin(angle);
    ball->setVel(xVel, yVel);
    SDL_Log("ball vel: %f, %f, int: %f, norm: %f, angle: %f, cos: %f, -sin: %f",
            xVel, yVel, intersect, normIntersect, angle, cos(angle),
            -sin(angle));
  }

  if (ballRec->y < (0 + (ballRec->h / 2)))
    ball->setVel(vel.x, -1 * vel.y);
  if (ballRec->y > (DIM_Y - (ballRec->h / 2)))
    ball->setVel(vel.x, -1 * vel.y);
}
