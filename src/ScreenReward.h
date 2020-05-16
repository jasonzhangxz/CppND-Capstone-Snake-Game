
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
  SDL_Point pos;
  int getTimeLeft();
  void setPos(int x, int y);

protected:
  bool isRewardCell(int x, int y);

// private:
  std::chrono::system_clock::time_point tStart,tNow;
  int expectDuration,timeLeft;
  void checkDuration();

};

#endif
