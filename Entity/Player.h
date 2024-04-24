#pragma once

#include "Mob.h"

namespace Genesis {

    class Player : public Mob
    {
    public:
        Player(int x, int y);

        virtual void OnUpdate(float ts) override;

        virtual EntityType GetType() const override { return EntityType::Player; }
    protected:
        virtual void UpdateSprite() override;
    private:
        void CheckFemaleCollision();
        std::pair<int, int> GenerateFemaleSpawn();
    private:
        bool m_Night = false;
    };

} // Genesis