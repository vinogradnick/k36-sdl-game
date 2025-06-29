#pragma once

#include "../AssetConfig.hpp"
#include "../Core/Context.hpp"
#include "../Core/Scene.hpp"

namespace WorldScene {
void Update(void *data, GameContext &ctx, const SceneManager &manager);
void Render(void *data, GameContext &ctx);
void Drop(void *data);
Scene createScene(GameContext &ctx);
} // namespace WorldScene