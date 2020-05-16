#ifndef SCREENBOMB_H
#define SCREENBOMB_H

#include <chrono>
#include "ScreenReward.h"
#include "SDL.h"

class ScreenBomb:public ScreenReward{
public:
  ScreenBomb(std::size_t grid_width, std::size_t grid_height);
  // ScreenBomb();
  // ~ScreenBomb();
  void run();
  void updatePos(ScreenReward& reward);
  // void updatePos();
  // SDL_Point pos;
  // int getTimeLeft();
  // void setbPos(int x, int y);

private:
  // std::chrono::system_clock::time_point tStart,tNow;
  // int bombDuration,timeLeft;
  void checkDuration();
  std::size_t grid_width_, grid_height_;
};

#endif
