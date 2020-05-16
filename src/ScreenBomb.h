#ifndef SCREENBOMB_H
#define SCREENBOMB_H

#include <chrono>
#include "ScreenObject.h"
#include "SDL.h"

class ScreenBomb:public ScreenObject{
public:
  ScreenBomb(std::size_t grid_width, std::size_t grid_height);
  // ScreenBomb();
  // ~ScreenBomb();
  void simulate();
  void updatePos();
  SDL_Point pos;
  int getTimeLeft();
  void setBombPos(int x, int y);

private:
  std::chrono::system_clock::time_point tStart,tNow;
  int bombDuration,timeLeft;
  void checkDuration();
};

#endif
