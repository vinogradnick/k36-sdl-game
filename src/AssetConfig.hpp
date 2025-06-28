#pragma once
namespace AppConfig {
namespace Path {
constexpr const char FONT_PATH[] = "assets/fonts.bmp";
constexpr const char LOADING_SCREEN[] = "assets/splashscreen.bmp";
} // namespace Path

namespace Window {

static constexpr int SCREEN_WIDTH = 640;
static constexpr int SCREEN_HEIGHT = 480;
constexpr const char SCREEN_TITLE[] = "K36 ARpgGame";
static constexpr int TARGET_FRAME_RATE_MS = 33;

static constexpr int SCREEN_CENTER_X = (SCREEN_WIDTH / 2) - 100;
static constexpr int SCREEN_CENTER_Y = (SCREEN_HEIGHT / 2);

} // namespace Window

} // namespace AppConfig
