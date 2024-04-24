#pragma once

#include <array>

#include "Menu.h"

namespace Genesis {
    class Game;

    class MainMenu : public Menu
    {
    public:
        MainMenu(Game& game);

        void OnUpdate(float ts) override;

        void OnRender() override;
    private:
        std::array<const char*, 3> m_Options = { "Play", "Help", "About" };
        int m_Selected = 0;
        Game& m_Game;
    };

} // Genesis