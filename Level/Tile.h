#pragma once

#include "Graphics/Sprite.h"

namespace Genesis {

    enum class TileType
    {
        None = 0,
        GrassGround,
        Stone,
        Grass,
        Flower ,
        Rock,
        SnowRock,
        Water,
        Snow,
        Ice,
        Tree,
        TreeTop,
        SnowTree,
        SnowTreeTop,
        Torch
    };

    struct Tile
    {
        TileType Type;
        Genesis::Sprite Sprite;
        bool Solid = false;
    };

    namespace Tiles {

        inline Tile GrassGround = { TileType::GrassGround, Sprites::GrassGround };
        inline Tile Stone = { TileType::Stone, Sprites::Stone, true };
        inline Tile Grass = { TileType::Grass, Sprites::Grass };
        inline Tile Flower  = { TileType::Flower, Sprites::Flower };
        inline Tile Rock = { TileType::Rock, Sprites::Rock, true };
        inline Tile SnowRock = { TileType::SnowRock, Sprites::SnowRock, true };
        inline Tile Water = { TileType::Water, Sprites::Water, true };
        inline Tile Snow = { TileType::Snow, Sprites::Snow };
        inline Tile Ice = { TileType::Ice, Sprites::Ice, true };
        inline Tile Tree = { TileType::Tree, Sprites::Tree0, true };
        inline Tile TreeTop = { TileType::TreeTop, Sprites::Tree2 };
        inline Tile SnowTree = { TileType::SnowTree, Sprites::SnowTree0, true };
        inline Tile SnowTreeTop = { TileType::SnowTreeTop, Sprites::SnowTree2 };
        inline Tile Torch = { TileType::Torch, Sprites::Torch };

    }


} // Genesis