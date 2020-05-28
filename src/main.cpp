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

  std::promise<bool> exitSignal;
  std::future<bool> running = exitSignal.get_future();

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Snake snake(kGridWidth, kGridHeight);
  ScreenFood food(kGridWidth, kGridHeight);
  std::thread th1(&ScreenFood::run, &food, std::move(running));

  Game game(kGridWidth, kGridHeight, snake, food);
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  exitSignal.set_value(std::move(snake.alive));
  th1.join();
  return 0;
}
