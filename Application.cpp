#include "Application.h"

#include "raylib.h"

#include <cmath>

#include "Sound/Sound.h"

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

    void Application::Loop()
    {
        m_Time += 0.0167f;
        OnUpdate();
        OnRender();

        while (GetTime() - m_LastTime > 1.0)
        {
            m_LastTime++;
            m_Game->OncePerSecond();
        }
    }

    void Application::StaticLoop()
    {
        s_Instance->Loop();
    }

    void Application::Run()
    {
        InitWindow(m_Specification.Width * m_Specification.Scale, m_Specification.Height * m_Specification.Scale, "Genesis");
        SetExitKey(0);
        m_Icon = LoadImage("res/icon.png");
        SetWindowIcon(m_Icon);

        SetTargetFPS(60);

        m_Renderer.Init();
        m_Game = std::make_unique<Game>();
        m_LastTime = GetTime();

#if defined(PLATFORM_WEB)
        emscripten_set_main_loop(StaticLoop, 0, 1);
#else
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            Loop();
        }
#endif
        CloseAudioDevice();
        CloseWindow();
        UnloadImage(m_Icon);
    }

    void Application::OnUpdate()
    {
        m_Game->OnUpdate(0.01667f);
        if (Sounds::MusicCurrentlyPlaying)
            UpdateMusicStream(Sounds::MusicCurrentlyPlaying->GetMusic());
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