#include <iostream>
#include "../headers/lib.hpp"
#include "../headers/pong.hpp"

Player::Player(int playerName) {
  playerName_ = playerName;
  points_ = 0;
  Point<int> dim = rectDims();
  rect_.w = dim.x;
  rect_.h = dim.y;
  rect_.x = getXPos();
  rect_.y = (DIM_Y * .5) - (rect_.h * .5);
  std::cout << "Player: " << playerName_ << std::endl;
  std::cout << "dim " << rect_.w << ", " << rect_.h << std::endl;
  std::cout << "pos " << rect_.x << ", " << rect_.y << std::endl;
}
void Player::posUp() { rect_.y -= 10; }
void Player::posDown() { rect_.y += 10; }
void Player::incrPoint() { points_++; }
void Player::reset() {
  rect_.y = DIM_Y / 2 - (rect_.h / 2);
  points_ = 0;
}
void Player::status() { SDL_Log("%d pos: %d", playerName_, rect_.y); }

Point<int> Player::rectDims() {
  Point<int> p;
  p.x = DIM_X * .04;
  p.y = DIM_Y * .15;
  return p;
}

int Player::getXPos() {
  int pos = DIM_X * .02;
  SDL_Log("xPos: %i", pos);
  if (playerName_ == 1) {
    return pos;
  }
  return DIM_X - pos - (rect_.w);
}

Ball::Ball() {
  rect_.w = DIM_X * .02;
  rect_.h = rect_.w;
  rect_.x = DIM_X / 2 - (rect_.h / 2);
  rect_.y = rect_.x;
  std::cout << "Ball" << std::endl;
  std::cout << "pos " << rect_.x << ", " << rect_.y << std::endl;
  std::cout << "vel " << vel_.x << ", " << vel_.y << std::endl;
}

Ball::~Ball() {}

void Ball::setVel(double x, double y) {
  vel_.x = x;
  vel_.y = y;
}

void Ball::setPos(double x, double y) {
  rect_.x = x;
  rect_.y = y;
}

void Ball::flipVel() {
  int t = vel_.x;
  vel_.x = vel_.y;
  vel_.y = t;
}

void Ball::status() {
  // SDL_Log("Ball pos: (%f, %f) vel: (%f, %f)", rect_.x, rect_.y, vel_.x,
  // vel_.y);
  SDL_Log("vel: (%f, %f)", vel_.x, vel_.y);
}

void Ball::reset() {
  double p = DIM_X / 2 - (rect_.h / 2);
  setPos(p, p);
  setVel(1, 0);
}
