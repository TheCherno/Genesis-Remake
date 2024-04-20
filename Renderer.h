#pragma once

#include "raylib.h"
#include <stdint.h>


namespace Genesis {

    class Renderer
    {
    public:
        Renderer(int width, int height);
        ~Renderer();

        void Init();

        void ClearRandom();

        const Texture2D& GetTexture() const { return m_Texture; }
    private:
        void Update();
    private:
        int m_Width = 0;
        int m_Height = 0;

        uint32_t* m_ImageBuffer = nullptr;
        Image m_Image;
        Texture2D m_Texture;
    };
}
