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
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  ScreenFood food;
  ScreenReward reward;
  ScreenBomb bomb;

  int score{0};
  int scoreTriggerReward{3};
  bool isBombValid{false};    //boolean to indicate whether bomb need to be showed up on screen
  bool isRewardValid{false};  //boolean to indicate whether reward need to be showed up on screen
  bool rewardInEffect{false}; //boolean to indicate whether reward is in effect
  int rewardTimeLeft{0};
  int bombTimeLeft{0};
  void PlaceFood();
  void PlaceReward();
  void PlaceBomb();
  void Update();
};

#endif
