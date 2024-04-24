#pragma once

#include "Mob.h"

namespace Genesis {

    class Female : public Mob
    {
    public:
        Female(int x, int y);

        void OnUpdate(float ts) override;

        virtual EntityType GetType() const override { return EntityType::Female; }
    protected:
        virtual void UpdateSprite() override;
    };

} // Genesis