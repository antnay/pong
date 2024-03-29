#ifndef _PONG_H_
#define _PONG_H_
#include "lib.h"

class Player {
public:
  Player(int playerNum);
  ~Player(){};
  int getNum() const { return playerNum_; }
  double getPos() const { return pos_; }
  int getPoints() const { return points_; };
  void posUp();
  void posDown();
  void incrPoint();
  void draw();
  void reset();

private:
  // Rectangle r;
  double width;
  double height;
  double pos_;
  int playerNum_;
  int points_;
};

class Ball {
public:
  Ball(double x, double y);
  ~Ball();
  Point<double> getPos() const { return pos_; }
  Point<double> getSpeed() const { return vec_; }
  bool hit(Player p);
  bool outOfBound();
  void update(double x, double y);
  void draw();
  void reset();

private:
  double radius;
  Point<double> pos_;
  Point<double> vec_;
};

#endif
