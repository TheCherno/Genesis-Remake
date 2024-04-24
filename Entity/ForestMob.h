#pragma once

#include "Mob.h"

namespace Genesis {

    class ForestMob : public Mob
    {
    public:
        ForestMob(int x, int y);

        void OnUpdate(float ts) override;

        EntityType GetType() const override { return EntityType::ForestMob; }
    protected:
        void UpdateSprite() override;
    };

} // Genesis