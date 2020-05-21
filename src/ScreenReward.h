
#ifndef SCREENREWARD_H
#define SCREENREWARD_H

#include <chrono>
#include "ScreenObject.h"
#include "SDL.h"

class ScreenReward:public ScreenObject{
public:
  ScreenReward(std::size_t grid_width, std::size_t grid_height);
  void updatePos();
  int getTimeLeft();
  void checkDuration();

protected:
  std::chrono::system_clock::time_point tStart,tNow;
  int expectDuration,timeLeft;

};

#endif
