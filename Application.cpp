#include "Application.h"

#include "raylib.h"

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

        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            OnUpdate();
        }
#endif
        CloseWindow();
    }

    void Application::OnUpdate()
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        m_Renderer.ClearRandom();

        DrawTextureEx(m_Renderer.GetTexture(), Vector2{0.0f, 0.0f}, 0, 3.0f,  WHITE);

        EndDrawing();
    }
} // Genesis