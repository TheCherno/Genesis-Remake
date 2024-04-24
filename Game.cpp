#include "Game.h"

#include "raylib.h"

namespace Genesis {

    Game::Game()
        : m_Population(m_Level)
    {
        m_Level.Load("res/levels/ocean.png");
        m_Level.Play = true;
    }

    void Game::OnUpdate(float ts)
    {
        m_Population.OnUpdate(ts);
        m_Level.OnUpdate(ts);
    }

    void Game::Render()
    {
        m_Level.OnRender();
    }

    void Game::RenderUI()
    {
        m_Population.OnRender();
        m_Level.RenderTimer();
    }

    void Game::OncePerSecond()
    {
        m_Level.UpdateTimer();
    }
} // Genesis