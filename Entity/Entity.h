#pragma once

#include "Level/Level.h"

namespace Genesis {

    class Entity
    {
    public:
        virtual ~Entity() = default;

        virtual void OnUpdate(float ts) {}
        virtual void OnRender() {}

        void OnInit(Level* level);

        void Remove();
    public:
        int X = 0, Y = 0;
    protected:
        Level* m_Level;
        bool m_Removed = false;
    };

} // Genesis