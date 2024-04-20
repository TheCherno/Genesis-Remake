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

    struct Tile {
        TileType Type;
        Genesis::Sprite Sprite;
    };

    namespace Tiles {

        inline Tile GrassGround = { TileType::GrassGround, Sprites::GrassGround };
        inline Tile Stone = { TileType::Stone, Sprites::Stone };
        inline Tile Grass = { TileType::Grass, Sprites::Grass };
        inline Tile Flower  = { TileType::Flower, Sprites::Flower };
        inline Tile Rock = { TileType::Rock, Sprites::Rock };
        inline Tile SnowRock = { TileType::SnowRock, Sprites::SnowRock };
        inline Tile Water = { TileType::Water, Sprites::Water };
        inline Tile Snow = { TileType::Snow, Sprites::Snow };
        inline Tile Ice = { TileType::Ice, Sprites::Ice };
        inline Tile Tree = { TileType::Tree, Sprites::Tree0 };
        inline Tile TreeTop = { TileType::TreeTop, Sprites::Tree2 };
        inline Tile SnowTree = { TileType::SnowTree, Sprites::SnowTree0 };
        inline Tile SnowTreeTop = { TileType::SnowTreeTop, Sprites::SnowTree2 };
        inline Tile Torch = { TileType::Torch, Sprites::Torch };


    }


} // Genesis