#pragma once

#include "../AssetConfig.hpp"
#include "../Core/Context.hpp"
#include "../Core/Scene.hpp"

namespace LoadingScene {
void Update(void *data, GameContext &ctx);
void Render(void *data, GameContext &ctx);
void Drop(void *data);
Scene createScene(GameContext &ctx);
} // namespace LoadingScene