#pragma once
#include "AssetConfig.hpp"
#include "Core/Context.hpp"
#include "Core/Scene.hpp"
#include "Scenes/LoadingScene.hpp"
#include <SDL2/SDL.h>

struct App {

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  GameContext ctx;
  SceneManager manager;
  bool running = true;

  explicit App(SDL_Renderer *renderer) : ctx(renderer) {

    manager.setScene(LoadingScene::createScene(ctx));
    ctx.assetServer.Prepare(
        {AppConfig::Path::LOADING_SCREEN, AppConfig::Path::FONT_PATH});
  }

  ~App() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void ClearScreen() const noexcept {
    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx.renderer);
  }

  void Run() {
    while (running) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
          running = false;
      }

      manager.update(ctx);
      ClearScreen();
      manager.render(ctx);
      SDL_RenderPresent(ctx.renderer);
    }
  }
};
