#include "pong.h"
#include <iostream>

Player::Player(int playerNum) {
  playerNum_ = playerNum;
  points_ = 0;
  pos_ = 150;
  std::cout << getPoints() << " " << getPos() << std::endl;
}
void Player::posUp() { pos_ += 5; }
void Player::posDown() { pos_ -= 5; }
void Player::incrPoint() { points_++; }
void Player::draw() {}
void Player::reset() {
  pos_ = 150;
  points_ = 0;
}

Ball::Ball(double x, double y) {
  pos_.x = x;
  pos_.y = y;
}

void Ball::reset() {}
