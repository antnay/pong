#ifndef _PONG_H_
#define _PONG_H_

class Player {
public:
  Player(int playerNum) {
    playerNum_ = playerNum;
    points_ = 0;
    pos_ = 150;
  }
  int getNum() const { return playerNum_; }
  double getPos() const { return pos_; }
  int getPoints() const { return points_; }
  void posUp() { playerNum_++; }
  void posDown() { playerNum_++; }

private:
  int playerNum_;
  double pos_;
  int points_;
};

#endif
