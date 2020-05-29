#include <random>
#include "ScreenFood.h"

ScreenFood::ScreenFood(std::size_t grid_width, std::size_t grid_height)
  :ScreenObject(grid_width,grid_height)
{
    this->updatePos();
}

ScreenFood::ScreenFood(const ScreenFood &food)
  :ScreenObject(food)
{
}

void ScreenFood::updatePos(){
  pos.x = random_w(engine);
  pos.y = random_h(engine);
}

void ScreenFood::run(){
  //empty function only print out a comment
  std::cout << "run food" << std::endl;
}
