#pragma once

#include "Entity.h"

namespace Genesis {

    class Mob : public Entity
    {
    public:
        void Move(int xa, int ya);
        bool Collision(int xa, int ya);
        bool Collision2(int xa, int ya);

        const Sprite& GetSprite() const { return m_Sprite; }
    protected:
        Sprite m_Sprite;
        int m_Dir = 0;
        float m_LightDist = -1.0f;
        bool m_Walking = false;

    };

} // Genesis