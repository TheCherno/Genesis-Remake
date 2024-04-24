#include "AboutMenu.h"

#include <array>

#include "Application.h"
#include "MainMenu.h"
#include "Sound/Sound.h"

namespace Genesis {

    AboutMenu::AboutMenu(Game& game)
        : m_Game(game)
    {
    }

    void AboutMenu::OnUpdate(float ts)
    {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ESCAPE))
        {
            Sounds::Menu.Play();
            m_Game.SetMenu<MainMenu>();
        }
    }

    void AboutMenu::OnRender()
    {
        const int Black = 0xff;
		const int White = 0xffffffff;

        constexpr std::array text = { "Genesis is a free game made by Yan Chernikov (The Cherno), for ", //
                "Ludum Dare, a 48 hour game development competition. This game", //
                "was made in just 20 hours however, due to me finishing Year 12, my",//
                "last year of school, and having tons of work to do. The theme for the",//
                "competition was \"Evolution\". All assets were made within 48 hours.",//
                " ",//
                "This was made for the 24th Ludum Dare compo, my first ever entry for", "Ludum Dare. Any questions, you can contact me by sending an email",//
                "to y@nchernikov.com, or checking out my YouTube channel,",//
                "youtube.com/thechernoproject, for more information, and to watch the",//
                "recorded live stream of the entire game being made.", "",//
                "Thanks for playing!" };

        Renderer& renderer = Application::GetRenderer();
        for (size_t i = 0; i < text.size(); i++)
        {
            renderer.RenderText(text[i], 20 + 2, 10 + i * 30 + 2, 30, 0, Black);
            renderer.RenderText(text[i], 20, 10 + i * 30, 30, 0, White);
        }
        renderer.RenderText(m_Option, 350 + 3, 465 + 3, 60, 1, Black);
        renderer.RenderText(m_Option, 350, 465, 60, 1, White);
    }
} // Genesis