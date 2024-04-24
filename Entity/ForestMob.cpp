#include "ForestMob.h"

#include "Random.h"

namespace Genesis {

    ForestMob::ForestMob(int x, int y)
    {
        X = x;
        Y = y;
    }

    void ForestMob::OnUpdate(float ts)
    {
        if (Random::UInt(39) == 0)
        {
            m_Xa = (int) Random::UInt(2) - 1;
            m_Ya = (int) Random::UInt(2) - 1;
        }

        m_Walking = m_Xa != 0 || m_Ya != 0;
        if (m_Walking)
            Move(m_Xa, m_Ya);

        // if (health <= 0) remove();
    }

    void ForestMob::UpdateSprite()
    {
        m_Anim++;
        if (m_Dir == 0)
        {
            m_Sprite = Sprites::Player0;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                m_Sprite = Sprites::Player1;
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
            m_Sprite = Sprites::Player4;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                if (m_Anim % 30 > 15)
                {
                    m_Sprite = Sprites::Player4;
                } else
                {
                    m_Sprite = Sprites::Player5;
                }
            }
        }
        if (m_Dir == 2)
        {
            m_Sprite = Sprites::Player2;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                m_Sprite = Sprites::Player3;
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
            m_Sprite = Sprites::Player4;
            m_SpriteFlip = 1;
            if (m_Walking)
            {
                if (m_Anim % 30 > 15)
                {
                    m_Sprite = Sprites::Player4;
                } else
                {
                    m_Sprite = Sprites::Player5;
                }
            }
        }
    }
} // Genesis
