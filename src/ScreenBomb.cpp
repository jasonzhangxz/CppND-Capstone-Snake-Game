#include <random>
#include <cmath>
#include "ScreenBomb.h"

ScreenBomb::ScreenBomb(std::size_t grid_width, std::size_t grid_height)
  :ScreenReward(grid_width, grid_height)
{
   grid_width_ = grid_width;
   grid_height_ = grid_height;
}

void ScreenBomb::run()
{
    // launch bomb function in a thread
    threads.emplace_back(std::thread(&ScreenBomb::checkDuration, this));
}

void ScreenBomb::updatePos(ScreenReward& reward){
  int x,y;
  std::uniform_int_distribution<int> offset{1, 5};
  x = offset(engine);
  y = offset(engine);
  //make the bomb position close to the reward, wrap around if it goes off the screen
  pos.x = fmod(reward.pos.x + x + grid_width_, grid_width_);
  pos.y = fmod(reward.pos.y + y + grid_height_, grid_height_);

  tStart = std::chrono::system_clock::now();
  //show the bomb on the screen for a random period (15-25s)
  std::uniform_int_distribution<int> dist{15, 25};
  expectDuration = dist(engine);
  timeLeft = expectDuration;
}
