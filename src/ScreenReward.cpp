#include <random>
#include "ScreenReward.h"

ScreenReward::ScreenReward(std::size_t grid_width, std::size_t grid_height)
  :ScreenObject(grid_width,grid_height)
{
    this->updatePos();
}

int ScreenReward::getTimeLeft(){
  return timeLeft;
}

void ScreenReward::run()
{
    // launch reward function in a thread
    threads.emplace_back(std::thread(&ScreenReward::checkDuration, this));
}

void ScreenReward::updatePos(){
  pos.x = random_w(engine);
  pos.y = random_h(engine);
  tStart = std::chrono::system_clock::now();
  //show the reward on the screen for a random period (5-15s)
  std::uniform_int_distribution<int> dist{5, 15};
  expectDuration = dist(engine);
  timeLeft = expectDuration;
}

void ScreenReward::checkDuration(){
  while(true){
    tNow = std::chrono::system_clock::now();
    auto elapse = std::chrono::duration_cast<std::chrono::seconds>( tNow - tStart ).count();
    timeLeft = expectDuration - elapse;
    if ((timeLeft <= 0) && (pos.x > 0)){
      setPos(-1,-1);//hide the Object from the screen 
    }
    // sleep for 500ms between two cycles
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}
