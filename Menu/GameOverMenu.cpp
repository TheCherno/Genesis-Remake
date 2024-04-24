#include "GameOverMenu.h"

#include <format>

#include "Application.h"
#include "Game.h"
#include "MainMenu.h"
#include "Graphics/Renderer.h"
#include "Sound/Sound.h"

namespace Genesis {

	GameOverMenu::GameOverMenu(Game& game)
	    : m_Game(game)
    {
    	Sounds::GameOver.Play();
		// Game.pop = null;
    }

    void GameOverMenu::OnUpdate(float ts)
    {
    	if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && m_Selected < m_Options.size())
    	{
    		m_Selected++;
    		Sounds::MenuCycle.Play();
    	}
    	if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && m_Selected > 0)
    	{
    		m_Selected--;
    		Sounds::MenuCycle.Play();
    	}

    	if (m_Selected < 0)
    		m_Selected = 0;
    	if (m_Selected > 1)
    		m_Selected = 1;

    	// Main Menu
    	if (m_Selected == 1)
    	{
    		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    		{
    			Sounds::Menu.Play();
    			m_Game.SetMenuLevel();
    			m_Game.SetMenu<MainMenu>();
    		}
    	}


    	if (m_Selected == 0 && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)))
    	{
    		Sounds::MenuTheme.Stop();
    		Sounds::Theme.Play();
    		Sounds::Start.Play();
    		m_Game.Play();
    		// PlayMenu.biome = 2; //random.nextInt(3);
    	}
    }

    void GameOverMenu::OnRender()
    {
		Renderer& renderer = Application::GetRenderer();

		const int Black = 0xff;
		const int White = 0xffffffff;

		//if (Game.level instanceof SnowLevel) col = 0;

		renderer.RenderText("Game Over!", 70 + 4, 10 + 4, 165, 1, Black);
		renderer.RenderText("Game Over!", 70, 10, 165, 1, White);
		renderer.RenderText("Tweet your score @TheCherno!", 252 + 3, 160 + 3, 40, 1, Black);
		renderer.RenderText("Tweet your score @TheCherno!", 252, 160, 40, 1, White);

		std::string text = std::format("Your population: {}", (uint64_t)Population::PopulationCount);
		size_t length = text.length();
		renderer.RenderText(text, 450 - length * 12 + 3, 250 + 3, 50, 1, Black);
		renderer.RenderText(text, 450 - length * 12, 250, 50, 1, White);
		for (size_t i = 0; i < m_Options.size(); i++)
		{
			std::string selectedOption;
			const char* option = m_Options[i];
			if (i == m_Selected)
			{
				selectedOption = std::format("> {} <", m_Options[i]);
				option = selectedOption.c_str();
			}

			renderer.RenderText(option, 300 + 3, 400 + i * 60 + 3, 50, 1, Black);
			renderer.RenderText(option, 300, 400 + i * 60, 50, 1, White);
		}
    }
} // Genesis