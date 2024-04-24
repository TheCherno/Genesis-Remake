#pragma once
#include <array>

#include "Menu.h"

namespace Genesis {
    class Game;

    class GameOverMenu : public Menu
    {
    public:
        GameOverMenu(Game& game);

        void OnUpdate(float ts) override;
        void OnRender() override;
    private:
        std::array<const char*, 2> m_Options = { "Play Again?", "Main Menu" };
        int m_Selected = 0;

        Game& m_Game;
    };

} // Genesis