#include "Renderer.h"

#include "../Random.h"
#include "SpriteSheet.h"
#include "Utils/Utils.h"

#include <format>

namespace Genesis {

    static constexpr const char* FontPath = "res/fonts/Lato-Regular.ttf";
    static constexpr const char* FontBoldPath = "res/fonts/Lato-Bold.ttf";

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
        uint32_t* spriteBuffer = &spriteSheetBuffer[
            (sprite.X * sprite.Size) + (sprite.Y * sprite.Size) * m_SpriteSheet.GetWidth()];

        for (int y = 0; y < sprite.Size; y++)
        {
            int yo = y + yp;
            for (int x = 0; x < sprite.Size; x++)
            {
                int xo = x + xp;
                if (xo < 0 || yo < 0 || xo >= m_Width || yo >= m_Height)
                    continue;

                uint32_t color = spriteBuffer[x + y * m_SpriteSheet.GetWidth()];
                if (color == 0xffff00ff || color == 0xff7f007f)
                    continue;

                if (sprite != Sprites::Torch)
                    color = ChangeBrightness(color, Level::Brightness);
                m_ImageBuffer[xo + yo * m_Width] = color;
            }
        }
    }

    void Renderer::RenderMob(int xp, int yp, Mob* mob, int flip)
    {
        xp -= m_ViewOffsetX;
        yp -= m_ViewOffsetY;

        const Sprite& sprite = mob->GetSprite();

        uint32_t* spriteSheetBuffer = m_SpriteSheet.GetImageBuffer();
        uint32_t* spriteBuffer = &spriteSheetBuffer[
            (sprite.X * sprite.Size) + (sprite.Y * sprite.Size) * m_SpriteSheet.GetWidth()];

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
                if (xo < 0 || xo >= m_Width)
                    continue;

                int xs = x;
                if (flip == 1 || flip == 3)
                    xs = (sprite.Size - 1) - xs;

                uint32_t color = spriteBuffer[xs + ys * m_SpriteSheet.GetWidth()];
                if (color == 0xffff00ff || color == 0xff7f007f)
                    continue;

                // Change female tag color
                if (mob->CanSpawnChild && color == 0xff2328BC)
                    color = 0xff5BD34E;

                float lightDist = mob->GetLightDistance();
                if (lightDist < 0.0f) // no light source nearby
                    color = ChangeBrightness(color, Level::Brightness);
                else
                    color = ChangeBrightness(color, (int) (lightDist * Level::Brightness * 0.009f));
                m_ImageBuffer[xo + yo * m_Width] = color;
            }
        }
    }

    void Renderer::RenderLight(int xp, int yp, Sprite sprite, int r, int g, int b, double intensity)
    {
        xp -= m_ViewOffsetX;
        yp -= m_ViewOffsetY;

        uint32_t* spriteSheetBuffer = m_SpriteSheet.GetImageBuffer();
        uint32_t* spriteBuffer = &spriteSheetBuffer[
            (sprite.X * sprite.Size) + (sprite.Y * sprite.Size) * m_SpriteSheet.GetWidth()];

        for (int y = 0; y < sprite.Size; y++)
        {
            int yt = y + yp;
            int ys = y;
            for (int x = 0; x < sprite.Size; x++)
            {
                int xt = x + xp;
                int xs = x;
                if (xt < -15 || xt >= m_Width || yt < -16 || yt >= m_Height)
                    break; // TODO(Yan): continue?

                if (xt < 0)
                    xt = 0;
                if (yt < 0)
                    yt = 0;

                uint32_t color = spriteBuffer[xs + ys * m_SpriteSheet.GetWidth()];
                if (color == 0xffff00ff || color == 0xff7f007f)
                    continue;

                color = Tint(color, r * intensity, g * intensity, b * intensity);
                m_ImageBuffer[xt + yt * m_Width] = color;
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

    void Renderer::RenderText(const char* string, int x, int y, int size, int style, int color)
    {
        Font* font = nullptr;

        auto& fonts = style > 0 ? m_BoldFonts : m_Fonts;

        if (!fonts.contains(size)) {
            const char *path = style > 0 ? FontBoldPath : FontPath;
            char *finalPath = Genesis::Utils::ResolvePath(path);

            fonts[size] = LoadFontEx(finalPath, size, nullptr, 0);

            free(finalPath);
        }

        font = &fonts.at(size);

        DrawTextEx(*font, string, {(float) x, (float) y}, size, 2.0f, GetColor(color));
    }

    void Renderer::RenderText(const std::string& string, int x, int y, int size, int style, int color)
    {
        RenderText(string.c_str(), x, y, size, style, color);
    }

    void Renderer::Update()
    {
        UpdateTexture(m_Texture, m_ImageBuffer);
    }

    Renderer::~Renderer()
    {
        delete[] m_ImageBuffer;
    }

    uint32_t Renderer::ChangeBrightness(int col, int amount)
    {
        int r = (col & 0xff0000) >> 16;
        int g = (col & 0xff00) >> 8;
        int b = (col & 0xff);
        if (amount > 0) amount = 0;
        if (amount < -150) amount = -150;

        r += amount;
        g += amount;
        b += amount;

        if (r < 0) r = 0;
        if (g < 0) g = 0;
        if (b < 0) b = 0;
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;

        return 0xff << 24 | r << 16 | g << 8 | b;
    }

    uint32_t Renderer::Tint(int col, double r, double g, double b)
    {
        int red = (col & 0xff0000) >> 16;
        int green = (col & 0xff00) >> 8;
        int blue = (col & 0xff);

        red += (int) r;
        green += (int) g;
        blue += (int) b;

        if (red < 0) red = 0;
        if (green < 0) green = 0;
        if (blue < 0) blue = 0;
        if (red > 255) red = 255;
        if (green > 255) green = 255;
        if (blue > 255) blue = 255;

        return 0xff << 24 | red << 16 | green << 8 | blue;
    }
}
