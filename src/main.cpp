#include "App.hpp"
#include <SDL2/SDL.h>

int main() {

  auto *window =
      SDL_CreateWindow(AppConfig::Window::SCREEN_TITLE, SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, AppConfig::Window::SCREEN_WIDTH,
                       AppConfig::Window::SCREEN_HEIGHT, 0);
  auto *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  App instance(renderer);

  instance.Run();
  return 0;
}
