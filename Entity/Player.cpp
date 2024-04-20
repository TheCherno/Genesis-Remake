#include "Player.h"

#include "Application.h"
#include "Graphics/Renderer.h"

namespace Genesis {

    Player::Player(int x, int y)
    {
        X = x;
        Y = y;
    }

    void Player::OnUpdate(float ts)
    {
        int xa = 0, ya = 0;

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            ya--;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            ya++;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            xa--;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            xa++;

        m_Walking = false;
        if (xa != 0 || ya != 0)
        {
            Move(xa, ya);
            m_Walking = true;
        }

        if (IsKeyDown(KEY_ESCAPE))
        {
            // back to main menu
        }

        // check collision with females
    }

    void Player::OnRender()
    {
        Renderer& renderer = Application::Get().GetRenderer();
        UpdateSprite();
        renderer.RenderMob(X, Y, this, m_SpriteFlip);
    }

    void Player::UpdateSprite()
    {
        m_Anim++;

        if (m_Dir == 0) {
            m_Sprite = Sprites::Player0;
            m_SpriteFlip = 0;
            if (m_Walking) {
                m_Sprite = Sprites::Player1;
                if (m_Anim % 30 > 15) {
                    m_SpriteFlip = 0;
                } else {
                    m_SpriteFlip = 1;
                }
            }
        }
        if (m_Dir == 1) {
            m_Sprite = Sprites::Player4;
            m_SpriteFlip = 0;
            if (m_Walking) {
                if (m_Anim % 30 > 15) {
                    m_Sprite = Sprites::Player4;
                } else {
                    m_Sprite = Sprites::Player5;
                }
            }
        }
        if (m_Dir == 2) {
            m_Sprite = Sprites::Player2;
            m_SpriteFlip = 0;
            if (m_Walking) {
                m_Sprite = Sprites::Player3;
                if (m_Anim % 30 > 15) {
                    m_SpriteFlip = 0;
                } else {
                    m_SpriteFlip = 1;
                }
            }

        }
        if (m_Dir == 3) {
            m_Sprite = Sprites::Player4;
            m_SpriteFlip = 1;
            if (m_Walking) {
                if (m_Anim % 30 > 15) {
                    m_Sprite = Sprites::Player4;
                } else {
                    m_Sprite = Sprites::Player5;
                }
            }
        }

    }
} // Genesis