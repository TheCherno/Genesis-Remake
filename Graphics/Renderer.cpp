#include "Renderer.h"

#include "../Random.h"
#include "SpriteSheet.h"

#include <format>

namespace Genesis {

    Renderer::Renderer(int width, int height)
        : m_Width(width), m_Height(height)
    {
        m_ImageBuffer = new uint32_t[width * height];
    }

    void Renderer::Init()
    {
        m_SpriteSheet = SpriteSheet("res/sprites.png");

        m_Image = GenImageColor(m_Width, m_Height, GetColor(0xff00ffff));
        m_Texture = LoadTextureFromImage(m_Image);
    }

    void Renderer::ClearRandom()
    {
        for (uint32_t i = 0; i < m_Width * m_Height; i++)
        {
            int random = Random::UInt();
            random |= (0xff << 24);
            m_ImageBuffer[i] = random;
        }
    }

    void Renderer::SetViewOffset(int x, int y)
    {
        m_ViewOffsetX = x;
        m_ViewOffsetY = y;
    }

    void Renderer::RenderSprite(int xp, int yp, Sprite sprite)
    {
        xp -= m_ViewOffsetX;
        yp -= m_ViewOffsetY;

        uint32_t* spriteSheetBuffer = m_SpriteSheet.GetImageBuffer();
        uint32_t* spriteBuffer = &spriteSheetBuffer[(sprite.X * sprite.Size) + (sprite.Y * sprite.Size) * m_SpriteSheet.GetWidth()];

        for (int y = 0; y < sprite.Size; y++)
        {
            int yo = y + yp;
            for (int x = 0; x < sprite.Size; x++)
            {
                int xo = x + xp;
                if (xo < 0 || yo < 0 || xo >= m_Width || yo >= m_Height)
                    continue;

                int color = spriteBuffer[x + y * m_SpriteSheet.GetWidth()];
                if (color == 0xffff00ff || color == 0xff7f007f)
                    continue;

                m_ImageBuffer[xo + yo * m_Width] = spriteBuffer[x + y * m_SpriteSheet.GetWidth()];
            }
        }
    }

    void Renderer::RenderMob(int xp, int yp, Mob* mob, int flip)
    {
        xp -= m_ViewOffsetX;
        yp -= m_ViewOffsetY;

        const Sprite& sprite = mob->GetSprite();

        uint32_t* spriteSheetBuffer = m_SpriteSheet.GetImageBuffer();
        uint32_t* spriteBuffer = &spriteSheetBuffer[(sprite.X * sprite.Size) + (sprite.Y * sprite.Size) * m_SpriteSheet.GetWidth()];

        for (int y = 0; y < sprite.Size; y++)
        {
            int yo = y + yp;
            if (yo < 0 || yo >= m_Height)
                continue;

            int ys = y;
            if (flip == 2 || flip == 3)
                ys = (sprite.Size - 1) - ys;

            for (int x = 0; x < sprite.Size; x++)
            {
                int xo = x + xp;
                if (xo < 0  || xo >= m_Width)
                    continue;

                int xs = x;
                if (flip == 1 || flip == 3)
                    xs = (sprite.Size - 1) - xs;

                int color = spriteBuffer[xs + ys * m_SpriteSheet.GetWidth()];
                if (color == 0xffff00ff || color == 0xff7f007f)
                    continue;

                m_ImageBuffer[xo + yo * m_Width] = spriteBuffer[xs + ys * m_SpriteSheet.GetWidth()];
            }
        }
    }

    void Renderer::RenderSpriteSheet(int xp, int yp)
    {
        xp -= m_ViewOffsetX;
        yp -= m_ViewOffsetY;

        uint32_t* spriteSheetBuffer = m_SpriteSheet.GetImageBuffer();
        for (int y = 0; y < m_SpriteSheet.GetHeight(); y++)
        {
            for (int x = 0; x < m_SpriteSheet.GetWidth(); x++)
            {
                int xo = x + xp;
                int yo = y + yp;
                if (xo < m_Width && yo < m_Height)
                {
                    int color = spriteSheetBuffer[x + y * m_SpriteSheet.GetWidth()];
                    m_ImageBuffer[xo + yo * m_Width] = color;
                }
            }

        }
    }

    void Renderer::Update()
    {
        UpdateTexture(m_Texture, m_ImageBuffer);
    }

    Renderer::~Renderer()
    {
        delete[] m_ImageBuffer;
    }

}
