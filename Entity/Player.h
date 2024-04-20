#pragma once

#include "Mob.h"

namespace Genesis {

    class Player : public Mob
    {
    public:
        Player(int x, int y);

        virtual void OnUpdate(float ts) override;
        virtual void OnRender() override;
    private:
        void UpdateSprite();
    private:
        int m_SpriteFlip = 0;
        int m_Anim = 0;
        bool m_Night = false;
    };

} // Genesis