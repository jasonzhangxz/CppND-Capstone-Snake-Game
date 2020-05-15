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
  ScreenBomb bomb;
  // SDL_Point food;
  //
  // std::random_device dev;
  // std::mt19937 engine;
  // std::uniform_int_distribution<int> random_w;
  // std::uniform_int_distribution<int> random_h;

  int score{0};
  int scoreTriggerBomb{3};
  bool isThereBomb{false};
  // std::size_t _gridWidth, _gridHeight;
  void PlaceFood();
  void PlaceBomb();
  void Update();
};

#endif
