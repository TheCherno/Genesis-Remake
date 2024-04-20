#pragma once

#include "Sprite.h"
#include "SpriteSheet.h"
#include "raylib.h"

#include <stdint.h>

#include "Entity/Player.h"

namespace Genesis {

    class Renderer
    {
    public:
        Renderer(int width, int height);
        ~Renderer();

        void Init();
        void Update();

        void ClearRandom();

        void SetViewOffset(int x, int y);

        void RenderSprite(int xp, int yp, Sprite sprite);
        void RenderMob(int xp, int yp, Mob* mob, int flip);
        void RenderSpriteSheet(int x, int y);

        int GetWidth() const { return m_Width;}
        int GetHeight() const { return m_Height;}
        const Texture2D& GetTexture() const { return m_Texture; }
    private:
        int m_Width = 0;
        int m_Height = 0;

        int m_ViewOffsetX = 0, m_ViewOffsetY = 0;

        uint32_t* m_ImageBuffer = nullptr;
        Image m_Image;
        Texture2D m_Texture;
        SpriteSheet m_SpriteSheet;
    };
}
