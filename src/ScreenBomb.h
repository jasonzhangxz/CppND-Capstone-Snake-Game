#ifndef SCREENBOMB_H
#define SCREENBOMB_H

#include <chrono>
#include "ScreenReward.h"
#include "SDL.h"

class ScreenBomb:public ScreenReward{
public:
  ScreenBomb(std::size_t grid_width, std::size_t grid_height);
  void updatePos(ScreenReward& reward);
  void run();

private:
  std::size_t grid_width_, grid_height_;
  int onScreenTimeLowBound{15};
  int onScreenTimeHighBound{25};
};

#endif
