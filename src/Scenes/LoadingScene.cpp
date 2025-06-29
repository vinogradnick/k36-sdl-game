#include "LoadingScene.hpp"
#include "../Core/Ticker.hpp"
#include "../Core/UI/ImageView.hpp"
#include "../Core/UI/ProgressView.hpp"
#include "../Core/UI/TextView.hpp"

namespace LoadingScene {

using SceneText = UI::TextView<AppConfig::Window::SCREEN_CENTER_X,
                               AppConfig::Window::SCREEN_CENTER_Y,
                               AppConfig::Path::FONT_PATH>;
using SceneImage = UI::ImageView<AppConfig::Window::SCREEN_WIDTH,
                                 AppConfig::Window::SCREEN_HEIGHT>;

struct SceneState {
  Ticker ticker;
  SceneText text;
  SceneImage banner;
  UI::ProgressView progress;
};

void Update(void *data, GameContext &, const SceneManager &) {
  auto *state = static_cast<SceneState *>(data);
  if (state->ticker.tick()) {
    state->progress.Inc();
  }
}
void Render(void *data, GameContext &ctx) {
  constexpr int progressOffset = 30;
  constexpr int height = AppConfig::Window::SCREEN_HEIGHT;
  constexpr int width = AppConfig::Window::SCREEN_WIDTH;

  auto *state = static_cast<SceneState *>(data);

  state->banner.Render(ctx);
  state->progress.Render<0, height - progressOffset, width, progressOffset>(
      ctx);
  state->text.Render(ctx, "LOADING WORLD");
}

void Drop(void *data) { delete static_cast<SceneState *>(data); }

Scene createScene(GameContext &ctx) {
  auto *ptr = new SceneState{Ticker(1000), SceneText(ctx),
                             SceneImage(ctx, AppConfig::Path::LOADING_SCREEN),
                             UI::ProgressView()};

  return Scene{
      ptr,
      &Update,
      &Render,
      &Drop,
  };
}
} // namespace LoadingScene