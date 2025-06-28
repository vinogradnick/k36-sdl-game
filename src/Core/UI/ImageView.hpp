#pragma once
#include "UI.hpp"

namespace UI {

template <const int Width, const int Height> struct ImageView {

  SDL_Texture *texture = nullptr;

  ImageView(GameContext &ctx, const char assetPath[])
      : texture(ctx.assetServer.Load(assetPath)) {}

  void Render(GameContext &ctx) {
    auto rect = SDL_Rect{0, 0, Width, Height};
    SDL_RenderCopy(ctx.renderer, texture, nullptr, &rect);
  }

  ~ImageView() { SDL_DestroyTexture(texture); }
};

} // namespace UI
