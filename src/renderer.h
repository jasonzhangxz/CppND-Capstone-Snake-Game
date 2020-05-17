#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &reward, SDL_Point const &bomb);
  void UpdateWindowTitle(int score, int fps, int timeReward, int timeBomb);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Surface *bombSur, *rewardSur;
  SDL_Surface *gScreenSurface;

  SDL_Texture *bombTex, *rewardTex;
  // SDL_Texture *texTarget;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
