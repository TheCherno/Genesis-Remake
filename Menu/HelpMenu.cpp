#include "HelpMenu.h"

#include <array>

#include "Application.h"
#include "Game.h"
#include "MainMenu.h"
#include "Sound/Sound.h"

namespace Genesis {

    HelpMenu::HelpMenu(Game& game)
        : m_Game(game)
    {
    }

    void HelpMenu::OnUpdate(float ts)
    {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE))
        {
            Sounds::Menu.Play();
            m_Game.SetMenu<MainMenu>();
        }
    }

    void HelpMenu::OnRender()
    {
	    const int Black = 0xff;
		const int White = 0xffffffff;

        constexpr std::array text = {
            "Hey what is up guys, my name is The Cherno, and welcome to a game.", //
            "The game has quite a simple concept. Use the arrow keys, or WASD", //
            "keys (if that's how you roll) to move your character. Your aim is to", //
            "evolve your colony; you must find women and walk through them,", //
            "creating a baby (or two). Everytime you do this, the rate of growth that", //
            "your population will experience is increased. Which means more women.", //
            "But here's the catch: you only have five minutes to build the largest", //
            "population this world has ever seen. Also, you can't breed with the same", //
            "woman twice. Women who have a green tag on them mean they're", //
            "available for breeding, while red means you've already nailed them. ;)", //
            "Women can be hard to find, however they always spawn in a similar", //
            "location.", //
            " ", "So try and find as many women as you can, to help grow the largest", //
            "population ever, evolving your nation to the maximum!"
        };

        Renderer& renderer = Application::GetRenderer();

        for (size_t i = 0; i < text.size(); i++)
        {
            renderer.RenderText(text[i], 10 + 2, 10 + i * 28 + 2, 28, 0, Black);
            renderer.RenderText(text[i], 10, 10 + i * 28, 28, 0, White);
        }
        renderer.RenderText(m_Option, 350 + 3, 465 + 3, 60, 1, Black);
        renderer.RenderText(m_Option, 350, 465, 60, 1, White);
    }
} // Genesis
