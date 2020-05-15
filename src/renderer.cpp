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

  boom  = SDL_LoadBMP("../images/bomb.bmp");
  if (boom == NULL){
    std::cout<<SDL_GetError()<<std::endl;
  } else {
    std::cout<<"image loaded"<<std::endl;
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyTexture(texTarget);
  SDL_DestroyTexture(bmpTex);
  // SDL_DestroyRenderer(sdl_renderer);
  SDL_FreeSurface(boom);
  boom = NULL;
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &bomb) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  // SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF); //yellow
  block.x = bomb.x * block.w;
  block.y = bomb.y * block.h;
  // SDL_RenderFillRect(sdl_renderer, &block);

  //render bomb

  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0x00); //black

  SDL_Rect *bblock = &block;
  // bblock->w = block.w;
  // bblock->h = block.h;
  // bblock->x = (food.x + 2)* block.w;
  // bblock->y = (food.y + 2)* block.h;


  //Get window surface
  // gScreenSurface = SDL_GetWindowSurface( sdl_window );
  // SDL_BlitScaled( boom, NULL, gScreenSurface, bblock );
  // //Update the surface
  // SDL_UpdateWindowSurface( sdl_window );

  bmpTex = SDL_CreateTextureFromSurface(sdl_renderer, boom);
  // SDL_FreeSurface(boom);
  // //Make a target texture to render too
	// texTarget = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_RGBA8888,
	// 	SDL_TEXTUREACCESS_TARGET, screen_width, screen_height);
  //
	// //Now render to the texture
	// SDL_SetRenderTarget(sdl_renderer, texTarget);
	SDL_RenderClear(sdl_renderer);
	SDL_RenderCopy(sdl_renderer, bmpTex, NULL, bblock);
	// //Detach the texture
	// SDL_SetRenderTarget(sdl_renderer, NULL);
  //
	// //Now render the texture target to our screen, but upside down
	// SDL_RenderClear(sdl_renderer);
	// SDL_RenderCopyEx(sdl_renderer, texTarget, NULL, bblock, 0, NULL, SDL_FLIP_VERTICAL);
  // SDL_RenderCopy(sdl_renderer, texTarget, NULL, bblock);
	// SDL_RenderPresent(sdl_renderer);

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

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
