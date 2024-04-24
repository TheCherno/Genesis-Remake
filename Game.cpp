#include "Game.h"

#include "Application.h"
#include "raylib.h"
#include "Entity/Female.h"
#include "Entity/ForestMob.h"
#include "Entity/Player.h"
#include "Menu/GameOverMenu.h"
#include "Menu/MainMenu.h"
#include "Sound/Sound.h"

namespace Genesis {

    Game::Game()
        : m_Level(*this)
    {
        SetMenuLevel();
        SetMenu<MainMenu>();
    }

    void Game::OnUpdate(float ts)
    {
        m_Time++;

        if (m_Menu)
            m_Menu->OnUpdate(ts);

        m_Level.OnUpdate(ts);

        if (IsKeyPressed(KEY_ESCAPE))
        {
            m_Level.Play = false;
            SetMenuLevel();
            SetMenu<MainMenu>();
        }
    }

    void Game::Render()
    {
        m_Level.OnRender();
    }

    void Game::RenderUI()
    {
        if (m_Menu)
            m_Menu->OnRender();

        m_Level.RenderUI();

        if (!IsWindowFocused())
        {
            if (m_Time % 50 > 18)
            {
                Renderer& renderer = Application::GetRenderer();
                renderer.RenderText("Click to Focus!", 120+5, 180+5, 120, 1, 0xff);
                renderer.RenderText("Click to Focus!", 120, 180, 120, 1, 0xffffffff);
            }
        }
    }

    void Game::OncePerSecond()
    {
        if (m_Level.Play)
            m_Level.UpdateTimer();
    }

    void Game::SetMenuLevel()
    {
        Sounds::MenuTheme.Play();
        m_Level.Load("res/levels/test.png");
        m_Level.AddPlayer(std::make_shared<Player>(180, 130));
        for (int i = 0; i < 20; i++)
            m_Level.Add(std::make_shared<ForestMob>(18 * 16, 18 * 16));
    }

    void Game::Play()
    {
        m_Level.Load("res/levels/ocean.png");
        m_Level.GetPlayer()->SetPosition(54 * 16, 23 * 16);
        m_Level.Add(std::make_shared<Female>(66 * 16, 26 * 16));

        m_Menu = nullptr;
        m_Level.Play = true;
    }
} // Genesis