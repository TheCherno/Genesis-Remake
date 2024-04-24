#include "Mob.h"

#include "Application.h"
#include "Graphics/Renderer.h"

namespace Genesis {

    void Mob::Move(int xa, int ya)
    {
        if (xa != 0 && ya != 0)
        {
            Move(xa, 0);
            Move(0, ya);
            return;
        }
        if (xa > 0)
            m_Dir = 1;
        if (xa < 0)
            m_Dir = 3;
        if (ya > 0)
            m_Dir = 2;
        if (ya < 0)
            m_Dir = 0;

        if (!Collision(xa, ya) && !Collision2(xa, ya))
        {
            X += xa;
            Y += ya;
        }
    }

    bool Mob::Collision(int xa, int ya)
    {
        bool solid = false;
        for (int i = 0; i < 4; i++)
        {
            int xt = ((X + xa) + (i % 2 * 2) * 5) >> 4;
            int yt = ((Y + ya) + (i / 2 * 2 - 4) * 2) >> 4;
            if (m_Level->GetTile(xt, yt + 1).Solid)
                solid = true;
        }
        return solid;
    }

    bool Mob::Collision2(int xa, int ya)
    {
        bool solid = false;
        for (int i = 0; i < 4; i++)
        {
            int xt = ((X + xa) + (i % 2 * 2 - 1) * 4) >> 4;
            int yt = ((Y + ya) + (i / 2 * 2 - 1) * 4) >> 4;
            if (m_Level->GetTile2(xt, yt).Solid)
                solid = true;
        }
        return solid;
    }

    void Mob::OnRender()
    {
        Renderer& renderer = Application::GetRenderer();
        UpdateSprite();
        renderer.RenderMob(X, Y, this, m_SpriteFlip);
    }
} // Genesis
