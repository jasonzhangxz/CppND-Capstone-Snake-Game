#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  bombSur  = SDL_LoadBMP("../images/bomb.bmp");
  if (bombSur == NULL){
    std::cout<<SDL_GetError()<<std::endl;
  } else {
    std::cout<<"bomb image loaded"<<std::endl;
    bombTex = SDL_CreateTextureFromSurface(sdl_renderer, bombSur);
    SDL_FreeSurface(bombSur);
    bombSur = NULL;
  }

  rewardSur  = SDL_LoadBMP("../images/reward.bmp");
  if (rewardSur == NULL){
    std::cout<<SDL_GetError()<<std::endl;
  } else {
    std::cout<<"Reward image loaded"<<std::endl;
    rewardTex = SDL_CreateTextureFromSurface(sdl_renderer, rewardSur);
    SDL_FreeSurface(rewardSur);
    rewardSur = NULL;
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyTexture(bombTex);
  SDL_DestroyTexture(rewardTex);
  SDL_DestroyRenderer(sdl_renderer);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, SDL_Point const &food, SDL_Point const &reward, SDL_Point const &bomb) {
  SDL_Rect block, bombBlock, rewardBlock;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  bombBlock.w = block.w;
  bombBlock.h = block.h;
  rewardBlock.w = block.w;
  rewardBlock.h = block.h;

  // Clear screen
  // SDL_RenderClear(sdl_renderer);
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0x00); //black

  // Clear screen
	SDL_RenderClear(sdl_renderer);

  //render bomb
  bombBlock.x = bomb.x * block.w;
  bombBlock.y = bomb.y * block.h;
	SDL_RenderCopy(sdl_renderer, bombTex, NULL, &bombBlock);

  //render reward
  rewardBlock.x = reward.x * block.w;
  rewardBlock.y = reward.y * block.h;
	SDL_RenderCopy(sdl_renderer, rewardTex, NULL, &rewardBlock);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); //yellow
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF); //white
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF); //blue
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); //red
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, int timeReward, int timeReducedSpeed, int timeBomb) {
  std::string title{"Score : " + std::to_string(score) + " " + '\t' + "FPS : " + std::to_string(fps) + "  " + '\t'};
  if (timeReward > 0) {
    title = title + "Reward vanish in (" + std::to_string(timeReward) + ") s." + '\t';
  } else if(timeReducedSpeed > 0){
    title = title + "LowSpd invalid in (" + std::to_string(timeReducedSpeed) + ") s." + '\t';
  } else {
    title = title + '\t' + '\t' + '\t' + '\t' + '\t'+'\t';
  }

  if (timeBomb > 0) {
    title = title + "Bomb vanish in (" + std::to_string(timeBomb)+ ") s." + '\t';
  } else {
    title = title + '\t' + '\t' + '\t' + '\t' + '\t';
  }

  SDL_SetWindowTitle(sdl_window, title.c_str());
}
