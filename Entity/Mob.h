#pragma once

#include "Entity.h"

namespace Genesis {

    class Mob : public Entity
    {
    public:
        virtual void OnRender() override;

        void Move(int xa, int ya);
        bool Collision(int xa, int ya);
        bool Collision2(int xa, int ya);

        float GetLightDistance() const { return m_LightDist; }

        const Sprite& GetSprite() const { return m_Sprite; }
    public:
        bool CanSpawnChild = false;
    protected:
        virtual void UpdateSprite() = 0;
    protected:
        Sprite m_Sprite;
        int m_Xa = 0, m_Ya = 0;
        int m_Dir = 0;
        bool m_Walking = false;

        int m_SpriteFlip = 0;
        int m_Anim = 0;
    };

} // Genesis