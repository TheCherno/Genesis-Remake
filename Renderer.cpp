#include "Renderer.h"

#include "Random.h"

namespace Genesis {

    Renderer::Renderer(int width, int height)
        : m_Width(width), m_Height(height)
    {
        m_ImageBuffer = new uint32_t[width * height];
    }

    void Renderer::Init()
    {
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

        Update();
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
