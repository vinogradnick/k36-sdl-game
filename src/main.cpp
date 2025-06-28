#include <cmath>
#include <cstdio>
#include <SDL2/SDL.h>
#include "AssetConfig.hpp"
#include "Core/Context.hpp"
#include "Core/Scene.hpp"
#include "Core/Ticker.hpp"
#include "scenes/LoadingScene.hpp"


void ClearScreen(GameContext & ctx)
{
    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx.renderer);
}


int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    GameContext ctx(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));
    SceneManager manager;

    manager.setScene(LoadingScene::createScene(ctx));

    ctx.assetServer.Prepare({AssetConfig::LOADING_SCREEN, AssetConfig::FONT_PATH});

    bool running = true;


    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        manager.update(ctx);
        ClearScreen(ctx);
        manager.render(ctx);

        SDL_RenderPresent(ctx.renderer);
    }


    SDL_DestroyRenderer(ctx.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
