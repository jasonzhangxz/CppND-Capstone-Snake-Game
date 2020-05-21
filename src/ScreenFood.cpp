#include <random>
#include "ScreenFood.h"

ScreenFood::ScreenFood(std::size_t grid_width, std::size_t grid_height)
  :ScreenObject(grid_width,grid_height)
{
    this->updatePos();
}

void ScreenFood::updatePos(){
  pos.x = random_w(engine);
  pos.y = random_h(engine);
}
