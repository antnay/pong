#ifndef _PONG_HPP_
#define _PONG_HPP_
#include "lib.hpp"

#define PLAYERSPEED 8
#define CENTER (DIM_X / 2 - (rect_.h / 2))
#define RECTHEIGHT (DIM_Y * .15)
#define BALLHEIGHT (DIM_X * .02)

class Player {
public:
  Player(int playerNum);
  ~Player();
  SDL_Rect *getRect() { return &rect_; }
  int getName() const { return playerName_; }
  int getPoints() const { return points_; };
  double getY() const { return rect_.y; }
  void posUp();
  void posDown();
  void incrPoint();
  void status();
  void reset();

private:
  Point<int> rectDims();
  int getXPos();
  int playerName_;
  int points_;
  SDL_Rect rect_;
};

class Ball {
public:
  Ball();
  ~Ball();
  SDL_Rect *getRect() { return &rect_; }
  Point<double> getPos();
  Point<double> getVel() const { return vel_; }
  void setVel(double x, double y);
  void flipVel();
  void setPos(double x, double y);
  bool hit(Player p);
  bool outOfBound();
  void status();
  void reset();

private:
  Point<double> rectPos();
  Point<double> vel_;
  SDL_Rect rect_;
};

#endif
