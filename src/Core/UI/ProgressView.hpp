#pragma once
#include "UI.hpp"

namespace UI {
struct ProgressView {
  int progress;

  explicit ProgressView() = default;

  template <const int PositionX, const int PositionY, const int Width,
            const int Height = Width>
  void Render(GameContext &ctx) {
    // Рисуем заполнение по горизонтали (заполняется слева направо)
    const int fillWidth = (Width * progress) / 100;
    SDL_Rect fillRect = {PositionX, PositionY, fillWidth, Height};
    SDL_SetRenderDrawColor(ctx.renderer, 0, 200, 0,
                           255); // зелёный цвет заполнения
    SDL_RenderFillRect(ctx.renderer, &fillRect);
  };

  void SetProgress(const int newProgress) { progress = newProgress; }

  void Inc(const int step = 1) { progress += step; };
  void Reset() { progress = 0; }

  ~ProgressView() = default;
};
} // namespace UI