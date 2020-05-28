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

void ScreenFood::run(std::future<bool> running){
  // launch Food function in a thread
  std::cout << "Thread Start" << std::endl;
  while (running.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout){
    placeFood();
  }
  std::cout << "Thread End" << std::endl;
}

void ScreenFood::placeFood(){
//  while (snake_.alive) {
//    while (true) {
    // Check that the location is not occupied by a snake item before placing
    // food.
//    if (snake_.SnakeCell(pos.x, pos.y)) {
//      updatePos();
//    }
//
//    snake_.Update();
//    int new_x = static_cast<int>(snake_.head_x);
//    int new_y = static_cast<int>(snake_.head_y);
//
//    // Check if there's food over here
//    if (pos.x == new_x && pos.y == new_y) {
//      snake_.GrowBody();
//      updatePos();
//    }

    // sleep for 2ms between two cycles
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

//  }
}
