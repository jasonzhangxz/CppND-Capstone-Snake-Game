#ifndef SCREENFOOD_H
#define SCREENFOOD_H

#include "ScreenObject.h"
#include "SDL.h"

class ScreenFood:public ScreenObject{
public:
  ScreenFood(std::size_t grid_width, std::size_t grid_height);

  void updatePos();

private:

};

#endif
