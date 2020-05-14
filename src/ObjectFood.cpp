#include <random>
#include "ObjectFood.h"

ObjectFood::ObjectFood(std::size_t grid_width, std::size_t grid_height)
  :ScreenObject(grid_width,grid_height)
{
    this->updatePos();
}


void ObjectFood::simulate()
{
    // launch Food function in a thread
    threads.emplace_back(std::thread(&ObjectFood::updatePos, this));
}

void ObjectFood::updatePos(){
  pos.x = random_w(engine);
  pos.y = random_h(engine);
}
