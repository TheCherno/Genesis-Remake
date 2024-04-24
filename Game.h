#pragma once

#include "Level/Level.h"
#include "Level/Population.h"
#include "Menu/Menu.h"

namespace Genesis {
    class MainMenu;

    class Game
    {
    public:
        Game();

        void OnUpdate(float ts);
        void OncePerSecond();

        void Render();
        void RenderUI();

        void Play();

        void SetMenuLevel();

        template<typename T>
        void SetMenu()
        {
            m_Menu = std::make_shared<T>(*this);
        }
    private:
        Level m_Level;

        std::shared_ptr<Menu> m_Menu;
        uint32_t m_Time = 0;
    };

} // Genesis