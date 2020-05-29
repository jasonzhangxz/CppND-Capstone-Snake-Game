#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "ScreenFood.h"
#include "ScreenBomb.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Snake &Snake, ScreenFood &Food,
          ScreenReward* Reward, ScreenBomb &Bomb);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  void PlaceFood();
  void PlaceReward();
  void PlaceBomb();
  void Update();
  Snake snake;
  ScreenFood food;
  ScreenReward* reward;
  ScreenBomb bomb;

  int score{0};
  int scoreTriggerReward{3};  //when it reaches this score, it will trigger the showup of reward/bomb on scree
  int rewardIncrement{5};     //place reward/bomb on the screen every # points
  bool isBombValid{false};    //boolean to indicate whether bomb need to be showed up on screen
  bool isRewardValid{false};  //boolean to indicate whether reward need to be showed up on screen
  bool rewardInEffect{false}; //boolean to indicate whether reward is in effect
  float rewardSpeed{0.1};     //when it hit the reward, keep the snake at initial speed for certain time
  float resumeSpeed;          //when the reward time is over, resume to this speed
  float speedIncrement{0.015};//increase the speed this much every food the snake eats
  int rewardTimeLeft{0};      //Afte this amount of time the reward will go away from the screen
  int bombTimeLeft{0};        //Afte this amount of time the bomb will go away from the screen
  int reducedSpeedTimeLeft{0};//when the snake hit the reward, to show how much time left for the slow speed
  int rewardTime{15};         //when the snake hit the reward, the speed keeps slow for thie long
  Uint32 reducedSpeedTimeStart;
};

#endif
