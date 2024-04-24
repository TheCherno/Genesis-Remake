#include "Female.h"

#include "Application.h"
#include "Random.h"
#include "Graphics/Renderer.h"

namespace Genesis {

    Female::Female(int x, int y)
    {
        X = x;
        Y = y;
        CanSpawnChild = true;
    }

    void Female::OnUpdate(float ts)
    {
        if (Random::UInt(40) == 0)
        {
            m_Xa = (int) Random::UInt(2) - 1;
            m_Ya = (int) Random::UInt(2) - 1;
        }
        if (m_Xa != 0 || m_Ya != 0)
        {
            m_Walking = true;
            Move(m_Xa, m_Ya);
        } else
        {
            m_Walking = false;
        }

        // if (m_Health <= 0) remove();
    }

    void Female::UpdateSprite()
    {
        m_Anim++;
        if (m_Dir == 0)
        {
            m_Sprite = Sprites::Female0;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                m_Sprite = Sprites::Female1;
                if (m_Anim % 30 > 15)
                {
                    m_SpriteFlip = 0;
                } else
                {
                    m_SpriteFlip = 1;
                }
            }
        }
        if (m_Dir == 1)
        {
            m_Sprite = Sprites::Female4;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                if (m_Anim % 30 > 15)
                {
                    m_Sprite = Sprites::Female4;
                } else
                {
                    m_Sprite = Sprites::Female5;
                }
            }
        }
        if (m_Dir == 2)
        {
            m_Sprite = Sprites::Female2;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                m_Sprite = Sprites::Female3;
                if (m_Anim % 30 > 15)
                {
                    m_SpriteFlip = 0;
                } else
                {
                    m_SpriteFlip = 1;
                }
            }
        }
        if (m_Dir == 3)
        {
            m_Sprite = Sprites::Female4;
            m_SpriteFlip = 1;
            if (m_Walking)
            {
                if (m_Anim % 30 > 15)
                {
                    m_Sprite = Sprites::Female4;
                } else
                {
                    m_Sprite = Sprites::Female5;
                }
            }
        }
    }
} // Genesis