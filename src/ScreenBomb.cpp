#include <random>
#include "ScreenBomb.h"

ScreenBomb::ScreenBomb(std::size_t grid_width, std::size_t grid_height)
  :ScreenObject(grid_width,grid_height)
{
    // this->updatePos();
    pos.x = -1;
    pos.y = -1;
    bombDuration = 0;
    timeLeft = 0;
}
// ScreenBomb::ScreenBomb(){
//   pos.x = -1;
//   pos.y = -1;
//   bombDuration = 0;
//   timeLeft = 0;
// }

ScreenBomb::~ScreenBomb(){
  //make the pos (-1,-1) means no need to render this Bomb object
  pos.x = -1;
  pos.y = -1;
  bombDuration = 0;
  timeLeft = 0;
}

int ScreenBomb::getTimeLeft(){
  return timeLeft;
}

void ScreenBomb::setBombPos(int x, int y){
  pos.x = x;
  pos.y = y;
}
void ScreenBomb::simulate()
{
    // launch bomb function in a thread
    threads.emplace_back(std::thread(&ScreenBomb::checkDuration, this));
}

void ScreenBomb::updatePos(){
  pos.x = random_w(engine);
  pos.y = random_h(engine);
  tStart = std::chrono::system_clock::now();
  //show the bomb on the screen for a random period (10-20s)
  std::uniform_int_distribution<int> dist{10, 20};
  bombDuration = dist(engine);
  // bombDuration = 10;
}

void ScreenBomb::checkDuration(){
  while(true){
    tNow = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>( tNow - tStart ).count();
    // std::cout<<"DURATION IS: "<<duration<<std::endl;
    timeLeft = bombDuration - duration;
    if ((timeLeft <= 0) && (pos.x == -1)){
      setBombPos(-1,-1);//hide the bomb Object
    }
    // sleep for 500ms between two cycles
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}
