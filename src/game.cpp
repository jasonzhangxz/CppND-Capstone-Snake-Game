#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      food(grid_width, grid_height),
      reward(grid_width, grid_height),
      bomb(grid_width, grid_height){
  PlaceFood();
  reward.setPos(-1,-1);//in the beginning hide the reward
  reward.run();
  bomb.setPos(-1,-1); //in the beginning hide the bomb
  bomb.run();

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
    renderer.Render(snake, food.pos, reward.pos, bomb.pos);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, rewardTimeLeft,reducedSpeedTimeLeft, bombTimeLeft);
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

void Game::PlaceReward() {
  reward.updatePos();
  while (true) {
    // Check that the location is not occupied by a snake item before placing
    // bomb.
    if (snake.SnakeCell(reward.pos.x, reward.pos.y)) {
      reward.updatePos();
    } else {
      return;
    }
  }
}

void Game::PlaceBomb() {
  bomb.updatePos(reward);//the bomb is going to be around the reward
  while (true) {
    // Check that the location is not occupied by a snake item before placing
    // bomb.
    if (snake.SnakeCell(bomb.pos.x, bomb.pos.y)) {
      bomb.updatePos(reward);
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
    if (rewardInEffect) {
      snake.speed = rewardSpeed;
    } else {
      snake.speed += 0.01; //TODO: change this back to +=0.02 to make the speed change more obvious
    }
  }

  if (isRewardValid) {
    // std::cout<<"Reward Screen time left: "<<reward.getTimeLeft()<<std::endl;
    rewardTimeLeft = reward.getTimeLeft();
    isRewardValid = (rewardTimeLeft > 0 ? true : false);
    if (reward.pos.x == new_x && reward.pos.y == new_y) {
      rewardInEffect = true;
      snake.speed = rewardSpeed;
      reward.setPos(-1,-1);
      isRewardValid = false;
      rewardTimeLeft = 0;
      reducedSpeedTimeLeft = 15;
      reducedSpeedTimeStart = SDL_GetTicks();
    }
  }

  if (rewardInEffect) {
    reducedSpeedTimeLeft = 15 - (SDL_GetTicks()-reducedSpeedTimeStart)/1000;
    if (reducedSpeedTimeLeft <= 0){
      rewardInEffect = false;
    }
  }

  if (isBombValid) {
    // std::cout<<"Bomb Screen time left: "<<bomb.getTimeLeft()<<std::endl;
    bombTimeLeft = bomb.getTimeLeft();
    isBombValid = (bombTimeLeft > 0 ? true : false);
    if (bomb.pos.x == new_x && bomb.pos.y == new_y) {
      snake.alive = false;
    }
  }

  if ((score > scoreTriggerReward) && (!isRewardValid) && (!isBombValid)){
    PlaceReward();
    PlaceBomb();
    isRewardValid = true;
    isBombValid = true;
    scoreTriggerReward += 5; //place new reward/bomb every 5 points
    // std::cout<<"Bomb Pos:"<<bomb.pos.x<<", "<<bomb.pos.y<<std::endl;
  }

}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
