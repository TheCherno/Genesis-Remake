#pragma once

namespace Genesis {

    struct Sprite
    {
        int X = 0;
        int Y = 0;
        int Size = 16;
    };

    namespace Sprites {
        inline Sprite GrassGround = {0, 0 };
        inline Sprite Stone = {1, 0 };
        inline Sprite Grass = {2, 0 };
        inline Sprite Flower = {3, 0 };
        inline Sprite Rock = {4, 0 };
        inline Sprite SnowRock = {3, 2 };
        inline Sprite Water = {1, 1 };
        inline Sprite Water2 = {2, 1 };
        inline Sprite Snow = {3, 1 };
        inline Sprite Ice = {4, 1 };

        inline Sprite Tree0 = {5, 0 };
        inline Sprite Tree1 = {6, 0 };
        inline Sprite Tree2 = {5, 1 };
        inline Sprite Tree3 = {6, 1 };

        inline Sprite SnowTree0 = {7, 0 };
        inline Sprite SnowTree1 = {8, 0 };
        inline Sprite SnowTree2 = {7, 1 };
        inline Sprite SnowTree3 = {8, 1 };

        inline Sprite Torch = {0, 1 };

        inline Sprite Player0 = {0, 7 };
        inline Sprite Player1 = {1, 7 };
        inline Sprite Player2 = {2, 7 };
        inline Sprite Player3 = {3, 7 };
        inline Sprite Player4 = {4, 7 };
        inline Sprite Player5 = {5, 7 };

        inline Sprite Female0 = {6, 7 };
        inline Sprite Female1 = {7, 7 };
        inline Sprite Female2 = {8, 7 };
        inline Sprite Female3 = {9, 7 };
        inline Sprite Female4 = {10, 7 };
        inline Sprite Female5 = {11, 7 };

        inline Sprite Predator0 = {0, 8 };
        inline Sprite Predator1 = {1, 8 };
        inline Sprite Predator2 = {2, 8 };

    }

} // Genesis