#pragma once

#include "Level/Level.h"
#include "Level/Population.h"

namespace Genesis {

    class Game
    {
    public:
        Game();

        void OnUpdate(float ts);
        void Render();
        void RenderUI();

        void OncePerSecond();

    private:
        Level m_Level;
        Population m_Population;
    };

} // Genesis