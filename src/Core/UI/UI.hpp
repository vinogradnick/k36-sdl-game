#ifndef UI_HPP
#define UI_HPP

#include <string_view>
#include <SDL2/SDL.h>
#include "../Context.hpp"
#include "../Tile.hpp"

namespace UI
{


using FontTile = Tile<16, 24, 0, 4>;
using FontAtlas = TileAtlas<FontTile, 8, 8>;

template <const int PositionX, const int PositionY>
struct UIComponent
{
    static constexpr auto positionX = PositionX;
    static constexpr auto positionY = PositionY;

    UIComponent() = default;
    ~UIComponent() = default;
};

template <const int PositionX, const int PositionY, const char * asset>
struct UITextView : UIComponent<PositionX, PositionY>
{
    FontAtlas atlas;

    explicit UITextView(GameContext & ctx)
        : atlas(FontAtlas::FromImage(ctx.renderer, asset))
    {
    }

    void Render(GameContext & ctx, const std::string_view & text)
    {
        auto cursorX = PositionX;
        auto cursorY = PositionY;

        for (const auto t : text)
        {
            auto tileIndex = static_cast<int>(t) - 'A';
            auto xPos = tileIndex % 8;
            auto yPos = tileIndex / 8;
            auto source = atlas.getTileRuntime(xPos, yPos);
            SDL_Rect dst = SDL_Rect{cursorX, cursorY, source.w, source.h};
            SDL_RenderCopy(ctx.renderer, atlas.texture, &source, &dst);
            cursorX += source.w;
        }
    }

    void RenderRuntime(GameContext & ctx, const FontAtlas & atlas, const std::string_view & text, const int fromX, const int fromY)
    {
        auto cursorX = fromX;
        auto cursorY = fromY;

        for (const auto t : text)
        {
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


template <const int Width, const int Height>
void ImageRender(GameContext & ctx, const char * assetImage)
{
    auto * img = ctx.assetServer.Load(assetImage);

    auto rect = SDL_Rect{0, 0, Width, Height};

    SDL_RenderCopy(ctx.renderer, img, nullptr, &rect);
}

template <const int PositionX, const int PositionY, const int Width, const int Height = Width>
void SquareProgress(GameContext & ctx, const int progress)
{
    // Рисуем заполнение по горизонтали (заполняется слева направо)
    const int fillWidth = (Width * progress) / 100;
    SDL_Rect fillRect = {PositionX, PositionY, fillWidth, Height};
    SDL_SetRenderDrawColor(ctx.renderer, 0, 200, 0, 255); // зелёный цвет заполнения
    SDL_RenderFillRect(ctx.renderer, &fillRect);
}


}

#endif