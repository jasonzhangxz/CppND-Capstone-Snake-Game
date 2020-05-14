#ifndef OBJECTFOOD_H
#define OBJECTFOOD_H

#include "ScreenObject.h"
#include "SDL.h"

class ObjectFood:public ScreenObject{
public:
  ObjectFood(std::size_t grid_width, std::size_t grid_height);
  // ~ObjectFood();
  void simulate();
  void updatePos();
  SDL_Point pos;

private:

};

#endif
