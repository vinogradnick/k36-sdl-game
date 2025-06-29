#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <initializer_list>
#include <string_view>
#include <unordered_map>

struct AssetServer {
  using TexturePtr = SDL_Texture *;
  SDL_Renderer *renderer;

  std::unordered_map<size_t, TexturePtr> assets;

  explicit AssetServer(SDL_Renderer *r) : renderer(r) {}

  AssetServer(const AssetServer &) = delete;
  AssetServer &operator=(const AssetServer &) = delete;

  void Prepare(const std::initializer_list<const char *> &sources) {
    for (const auto &source : sources) {
      Load(source);
    }
  }

  SDL_Texture *Load(const char *path) {

    auto hash = std::hash<std::string_view>{}(path);

    auto it = assets.find(hash);
    if (it != assets.end())
      return it->second;

    auto *container = SDL_LoadBMP(path);
    auto *texture = SDL_CreateTextureFromSurface(renderer, container);
    SDL_FreeSurface(container);

    if (!texture) {
      SDL_Log("AsssetServer dosen't work");
      return nullptr;
    }

    assets[hash] = texture;

    return texture;
  };

  void Drop(const char *path) {
    auto hash = std::hash<std::string_view>{}(path);
    auto it = assets.find(hash);
    if (it != assets.end()) {
      SDL_DestroyTexture(it->second);
      assets.erase(it);
    }
  }
  ~AssetServer() {
    for (auto &[_, ptr] : assets) {
      SDL_DestroyTexture(ptr);
    }
    assets.clear();
  };
};