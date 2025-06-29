
#include "WorldScene.hpp"

namespace WorldScene {

struct WorldState {};

void Update(void *data, GameContext &, const SceneManager &) {}
void Render(void *data, GameContext &ctx) {}

void Drop(void *data) {}

Scene createScene(GameContext &ctx) {
  auto *ptr = new WorldState{};

  return Scene{
      ptr,
      &Update,
      &Render,
      &Drop,
  };
}
} // namespace WorldScene