#include "Application.h"

#include "raylib.h"

#include <cmath>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

namespace Genesis {

    static Application* s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& spec)
        : m_Specification(spec), m_Renderer(spec.Width, spec.Height)
    {
        s_Instance = this;
    }

    Application::~Application()
    {
        s_Instance = nullptr;
    }

    Application& Application::Get()
    {
        // assert
        return *s_Instance;
    }

    void Application::Run()
    {
        InitWindow(m_Specification.Width * m_Specification.Scale, m_Specification.Height * m_Specification.Scale, "Genesis");
#if defined(PLATFORM_WEB)
        emscripten_set_main_loop([this](){ OnUpdate(); }, 0, 1);
#else
        SetTargetFPS(60);

        m_Renderer.Init();

        m_Game = std::make_unique<Game>();

        double lastTime = GetTime();

        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            m_Time += 0.0167f;
            OnUpdate();
            OnRender();

            while (GetTime() - lastTime > 1.0)
            {
                lastTime++;
                m_Game->OncePerSecond();
            }
        }
#endif
        CloseWindow();
    }

    void Application::OnUpdate()
    {
        m_Game->OnUpdate(0.01667f);
    }

    void Application::OnRender()
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        m_Renderer.ClearRandom();
        // m_Renderer.RenderSprite(50, 50, Sprites::torch);

        m_Game->Render();

        m_Renderer.Update();
        DrawTextureEx(m_Renderer.GetTexture(), Vector2{0.0f, 0.0f}, 0, (float)m_Specification.Scale,  WHITE);
        m_Game->RenderUI();

        EndDrawing();
    }
} // Genesis