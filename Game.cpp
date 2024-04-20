#include "Game.h"

#include "raylib.h"

namespace Genesis {

    Game::Game()
    {
        m_Level.Load("res/levels/ocean.png");
    }

    void Game::OnUpdate(float ts)
    {
        m_Level.OnUpdate(ts);
    }

    void Game::Render()
    {
        m_Level.OnRender();
    }
} // Genesis