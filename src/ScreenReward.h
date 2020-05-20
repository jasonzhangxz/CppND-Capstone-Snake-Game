
#ifndef SCREENREWARD_H
#define SCREENREWARD_H

#include <chrono>
#include "ScreenObject.h"
#include "SDL.h"

class ScreenReward:public ScreenObject{
public:
  ScreenReward(std::size_t grid_width, std::size_t grid_height);
  void run();
  void updatePos();
  int getTimeLeft();

protected:
  std::chrono::system_clock::time_point tStart,tNow;
  int expectDuration,timeLeft;
  void checkDuration();

};

#endif
