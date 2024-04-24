#pragma once

#include "Menu.h"

namespace Genesis {

    class Game;

    class HelpMenu : public Menu
    {
    public:
        HelpMenu(Game& game);
        void OnUpdate(float ts) override;

        void OnRender() override;
    private:
        Game& m_Game;

        const char* m_Option = "> Back <";
    };

} // Genesis