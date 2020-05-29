#include <random>
#include <cmath>
#include "ScreenBomb.h"

ScreenBomb::ScreenBomb(std::size_t grid_width, std::size_t grid_height)
  :ScreenReward(grid_width, grid_height),
   grid_width_(grid_width),grid_height_(grid_height)
{
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
  std::uniform_int_distribution<int> dist{onScreenTimeLowBound, onScreenTimeHighBound};
  expectDuration = dist(engine);
  timeLeft = expectDuration;
  // std::cout<<"Bomb updatePos() ExpectDuration "<<expectDuration<<" ;timeLeft: "<<timeLeft<<std::endl;

}


void ScreenBomb::run(std::future<bool> running)
{
    // launch bomb function in a thread
    std::cout << "Bomb Thread Start" << std::endl;
    while (running.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout){
        checkDuration();
        // sleep for 500ms between two cycles
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // std::cout<<"Bomb ExpectDuration "<<expectDuration<<" ;timeLeft: "<<timeLeft<<std::endl;

    }
    std::cout << "Bomb Thread End" << std::endl;
}
