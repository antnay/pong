#ifndef _GAME_HPP_
#define _GAME_HPP_
#include "pong.hpp"

bool getKey(SDL_Event &e, bool quit, Ball *&ball);
void score (Ball *ball, Player *playerOne, Player *playerTwo);
void movePlayerOne(Player *&player);
void movePlayerTwo(Player *&player);
void gameRender(SDL_Renderer *&renderer, Player *playerOne, Player *playerTwo,
                Ball *ball, SDL_Rect *centerRect);
std::vector<SDL_Point> PixelizeCircle(SDL_Point center, int radius);
void renderCircle(SDL_Renderer *renderer, std::vector<SDL_Vertex> &ballVec,
                  std::vector<int> inds, int centerX, int centerY);
void serveBall(SDL_Renderer *renderer, Ball *&ball);
void moveBall(Ball *&ball, Player *playerOne, Player *playerTwo);
void collision(Ball *&ball, Player *playerOne, Player *playerTwo);
#endif
