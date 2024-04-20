#pragma once

#include "Level/Level.h"

namespace Genesis {

    class Game
    {
    public:
        Game();

        void OnUpdate(float ts);
        void Render();
    private:
        Level m_Level;
    };

} // Genesis