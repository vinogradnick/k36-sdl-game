#pragma once
#include "../Context.hpp"
#include "../Tile.hpp"
#include "Component.hpp"
#include <SDL2/SDL.h>
#include <string_view>

namespace UI {
using FontTile = Tile<16, 24, 0, 4>;
using FontAtlas = TileAtlas<FontTile, 8, 8>;

template <const int PositionX, const int PositionY, const char *asset>
struct TextView : UIComponent<PositionX, PositionY> {
  FontAtlas atlas;

  explicit TextView(GameContext &ctx)
      : atlas(FontAtlas::FromImage(ctx.renderer, asset)) {}

  void Render(GameContext &ctx, const std::string_view &text) {
    auto cursorX = PositionX;
    auto cursorY = PositionY;

    for (const auto t : text) {
      auto tileIndex = static_cast<int>(t) - 'A';
      auto xPos = tileIndex % 8;
      auto yPos = tileIndex / 8;
      auto source = atlas.getTileRuntime(xPos, yPos);
      SDL_Rect dst = SDL_Rect{cursorX, cursorY, source.w, source.h};
      SDL_RenderCopy(ctx.renderer, atlas.texture, &source, &dst);
      cursorX += source.w;
    }
  }

  void RenderRuntime(GameContext &ctx, const std::string_view &text,
                     const int fromX, const int fromY) {
    auto cursorX = fromX;
    auto cursorY = fromY;

    for (const auto t : text) {
      auto tileIndex = static_cast<int>(t) - 'A';
      auto xPos = tileIndex % 8;
      auto yPos = tileIndex / 8;
      auto source = atlas.getTileRuntime(xPos, yPos);
      SDL_Rect dst = SDL_Rect{cursorX, cursorY, source.w, source.h};
      SDL_RenderCopy(ctx.renderer, atlas.texture, &source, &dst);
      cursorX += source.w;
    }
  }
};
} // namespace UI