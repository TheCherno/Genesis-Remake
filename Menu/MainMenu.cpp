#include "MainMenu.h"

#include <format>

#include "AboutMenu.h"
#include "Application.h"
#include "HelpMenu.h"
#include "Graphics/Renderer.h"
#include "Sound/Sound.h"

namespace Genesis {

	MainMenu::MainMenu(Game& game)
		: m_Game(game)
	{
	}

    void MainMenu::OnUpdate(float ts)
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
    	if (m_Selected > 2)
			m_Selected = 2;

		// Help Menu
    	if (m_Selected == 1)
		{
    		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    		{
    			Sounds::Menu.Play();
    			m_Game.SetMenu<HelpMenu>();
    		}
    	}

    	if (m_Selected == 2)
		{
    		if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
    		{
    			Sounds::Menu.Play();
    			m_Game.SetMenu<AboutMenu>();
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

    void MainMenu::OnRender()
    {
    	Renderer& renderer = Application::GetRenderer();

		const int Black = 0xff;
		const int White = 0xffffffff;
		const int Orange = 0xffaf00ff; // RGBA

        renderer.RenderText("Genesis", 170 + 5, 20 + 5, 160, 1, Black);
		renderer.RenderText("Genesis", 170, 20, 160, 1, White);
		renderer.RenderText("C++!", 650 + 3, 40 + 3, 60, 1, Black);
		renderer.RenderText("C++!", 650, 40, 60, 1, Orange);
		renderer.RenderText("A game by Yan Chernikov.", 270 + 2, 160 + 2, 40, 1, Black);
		renderer.RenderText("A game by Yan Chernikov.", 270, 160, 40, 1, White);
		for (size_t i = 0; i < m_Options.size(); i++)
		{
			std::string selectedOption;
			const char* option = m_Options[i];
			if (i == m_Selected)
			{
				selectedOption = std::format("> {} <", m_Options[i]);
				option = selectedOption.c_str();
			}
			renderer.RenderText(option, 350 + 3, 350 + i * 60 + 3, 50, 1, Black);
			renderer.RenderText(option, 350, 350 + i * 60, 50, 1, White);
		}
    }
} // Genesis