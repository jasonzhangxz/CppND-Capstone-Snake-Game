#include <random>
#include <cmath>
#include "ScreenBomb.h"

ScreenBomb::ScreenBomb(std::size_t grid_width, std::size_t grid_height)
  :ScreenReward(grid_width, grid_height)
{
   grid_width_ = grid_width;
   grid_height_ = grid_height;
}
// ScreenBomb::ScreenBomb(){
//   pos.x = -1;
//   pos.y = -1;
//   bombDuration = 0;
//   timeLeft = 0;
// }

// ScreenBomb::~ScreenBomb(){
//   //make the pos (-1,-1) means no need to render this Bomb object
//   pos.x = -1;
//   pos.y = -1;
//   bombDuration = 0;
//   timeLeft = 0;
// }

// int ScreenBomb::getTimeLeft(){
//   return timeLeft;
// }

// void ScreenBomb::setBombPos(int x, int y){
//   pos.x = x;
//   pos.y = y;
// }
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
  //show the bomb on the screen for a random period (10-20s)
  std::uniform_int_distribution<int> dist{5, 10};
  expectDuration = dist(engine);
  timeLeft = expectDuration;
}

void ScreenBomb::checkDuration(){
  while(true){
    tNow = std::chrono::system_clock::now();
    auto elapse = std::chrono::duration_cast<std::chrono::seconds>( tNow - tStart ).count();
    // std::cout<<"DURATION IS: "<<duration<<std::endl;
    timeLeft = expectDuration - elapse;
    if ((timeLeft <= 0) && (pos.x > 0)){
      setPos(-1,-1);//hide the bomb Object
    }
    // sleep for 500ms between two cycles
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}
