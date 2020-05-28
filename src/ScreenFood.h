#ifndef SCREENFOOD_H
#define SCREENFOOD_H

#include "ScreenObject.h"
#include "SDL.h"
#include "snake.h"
#include <future>

class ScreenFood:public ScreenObject{
public:
  ScreenFood(std::size_t grid_width, std::size_t grid_height);
  ScreenFood(const ScreenFood &food);

  void updatePos();
  void run(std::future<bool> running);

private:
  void placeFood();

};

#endif
