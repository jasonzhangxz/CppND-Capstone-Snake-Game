#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      food(grid_width, grid_height),
      bomb(grid_width, grid_height){
  PlaceFood();
  bomb.setBombPos(-1,-1);
  bomb.simulate();

}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food.pos, bomb.pos);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {

  while (true) {
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (snake.SnakeCell(food.pos.x, food.pos.y)) {
      food.updatePos();
    } else {
      return;
    }
  }
}

void Game::PlaceBomb() {
  bomb.updatePos();
  while (true) {
    // Check that the location is not occupied by a snake item before placing
    // bomb.
    if (snake.SnakeCell(bomb.pos.x, bomb.pos.y)) {
      bomb.updatePos();
    } else {
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.pos.x == new_x && food.pos.y == new_y) {
    score++;
    PlaceFood();
    std::cout<<"New Food Pos:"<<food.pos.x<<", "<<food.pos.y<<std::endl;
    // Grow snake and increase speed.
    snake.GrowBody();
    // snake.speed += 0.01;
  }

  if ((score > scoreTriggerBomb) && (!isThereBomb)){
    std::cout<<"PLACED A BOMB!!!"<<std::endl;
    // bomb.updatePos();
    PlaceBomb();
    isThereBomb = true;
    scoreTriggerBomb += 5; //place new bomb every 5 points
    std::cout<<"Bomb Pos:"<<bomb.pos.x<<", "<<bomb.pos.y<<std::endl;
  }

  if (isThereBomb) {
    std::cout<<"Bomb Screen time left: "<<bomb.getTimeLeft()<<std::endl;
    isThereBomb = (bomb.getTimeLeft() > 0 ? true : false);
    // if (bomb.getTimeLeft() > 0){
    //   isThereBomb = true;
    // } else {
    //   isThereBomb = false;
    //   bomb.setBombPos(-1,-1);
    // }
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
