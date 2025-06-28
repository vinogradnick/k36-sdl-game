#ifndef TILE_HPP
#define TILE_HPP

#include <SDL2/SDL.h>


template <const size_t Width, const size_t Height, const size_t OffsetX = 0, const size_t OffsetY = 0>
struct Tile
{
    static constexpr auto get_offset_y() noexcept { return OffsetY; }
    static constexpr auto get_offset_x() noexcept { return OffsetX; }
    static constexpr auto get_width() noexcept { return Width; }
    static constexpr auto get_height() noexcept { return Height; }

    static constexpr SDL_Rect getContainer(const int x, const int y) noexcept { return SDL_Rect{x, y, Width, Height}; };
};


template <typename Tile, int XPadding, int YPadding>
struct TileAtlas
{
    SDL_Texture * texture = nullptr;
    template <const int YPos, const int XPos>
    static constexpr SDL_Rect getTile() noexcept
    {
        constexpr auto x = ((XPos * Tile::get_width()) + XPos * Tile::get_offset_x());
        constexpr auto y = ((YPos * Tile::get_height()) + YPos * Tile::get_offset_y());

        return Tile::getContainer(x + XPadding, y + YPadding);
    }


    SDL_Rect getTileRuntime(const int x, const int y) const noexcept
    {
        auto xlcoal = ((x * Tile::get_width()) + x * Tile::get_offset_x());
        auto ylocal = ((y * Tile::get_height()) + y * Tile::get_offset_y());

        return Tile::getContainer(xlcoal + XPadding, ylocal + YPadding);
    }

    static constexpr TileAtlas FromImage(SDL_Renderer * renderer, const char * path)
    {
        auto * container = SDL_LoadBMP(path);
        auto * texture = SDL_CreateTextureFromSurface(renderer, container);
        SDL_FreeSurface(container);
        return TileAtlas{texture};
    }

    ~TileAtlas()
    {
        if (texture)
        {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
};
#endif // TILE_HPP
