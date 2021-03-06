
#ifndef SCREENREWARD_H
#define SCREENREWARD_H

#include <chrono>
#include <future>
#include "ScreenObject.h"
#include "SDL.h"

class ScreenReward:public ScreenObject{
public:
  ScreenReward(std::size_t grid_width, std::size_t grid_height);
  void updatePos();
  int getTimeLeft();
  void run(std::future<bool> running);

protected:
  std::chrono::system_clock::time_point tStart,tNow;
  int expectDuration,timeLeft;
  int onScreenTimeLowBound{5};
  int onScreenTimeHighBound{10};

  void checkDuration();
};

#endif
