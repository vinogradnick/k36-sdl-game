#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SDL2/SDL_render.h>
#include "AssetServer.hpp"


struct GameContext
{
    SDL_Renderer * renderer = nullptr;
    AssetServer assetServer;


    explicit GameContext(SDL_Renderer * r)
        : renderer(r)
        , assetServer(r)
    {
    }

    GameContext(const GameContext &) = delete;
    GameContext & operator=(const GameContext &) = delete;
    GameContext(GameContext &&) = delete;
    GameContext & operator=(GameContext &&) = delete;
};
#endif // CONTEXT_HPP
