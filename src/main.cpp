#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "ScreenFood.h"
#include "snake.h"
#include <memory>
#include <thread>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  std::promise<bool> exitSignal1, exitSignal2;
  std::future<bool> running1 = exitSignal1.get_future();
  std::future<bool> running2 = exitSignal2.get_future();

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Snake snake(kGridWidth, kGridHeight);
//  ScreenFood* food = new ScreenFood(kGridWidth, kGridHeight);
    std::unique_ptr<ScreenFood> food(new ScreenFood(kGridWidth, kGridHeight));

//  ScreenReward* reward = new ScreenReward(kGridWidth, kGridHeight);
  std::unique_ptr<ScreenReward> reward(new ScreenReward(kGridWidth, kGridHeight));
  std::thread th1(&ScreenReward::run, reward.get(), std::move(running1));

//  ScreenBomb* bomb = new ScreenBomb(kGridWidth, kGridHeight);
  std::unique_ptr<ScreenBomb> bomb(new ScreenBomb(kGridWidth, kGridHeight));
  std::thread th2(&ScreenBomb::run, bomb.get(), std::move(running2));

  Game game(kGridWidth, kGridHeight, snake, std::move(food), std::move(reward), std::move(bomb));
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  exitSignal1.set_value((snake.alive));
  exitSignal2.set_value((snake.alive));

  th1.join();
  th2.join();

//  delete food;
//  delete reward;
//  delete bomb;

  return 0;
}
