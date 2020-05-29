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

  std::promise<bool> exitSignal1, exitSignal2, exitSignal3;
  std::future<bool> running1 = exitSignal1.get_future();
  std::future<bool> running2 = exitSignal2.get_future();
  std::future<bool> running3 = exitSignal3.get_future();

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Snake snake(kGridWidth, kGridHeight);
  ScreenFood food(kGridWidth, kGridHeight);
  std::thread th1(&ScreenFood::run, &food, std::move(running1));

  ScreenReward reward(kGridWidth, kGridHeight);
  std::thread th2(&ScreenReward::run, &reward, std::move(running2));

  ScreenBomb bomb(kGridWidth, kGridHeight);
  std::thread th3(&ScreenBomb::run, &bomb, std::move(running3));

  Game game(kGridWidth, kGridHeight, snake, food, reward, bomb);
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  exitSignal1.set_value((snake.alive));
  exitSignal2.set_value((snake.alive));
  exitSignal3.set_value((snake.alive));
  th1.join();
  th2.join();
  th3.join();
  return 0;
}
