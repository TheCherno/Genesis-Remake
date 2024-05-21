#pragma once

#include <string>

#include "Graphics/Renderer.h"
#include "Level/Level.h"
#include "Game.h"

namespace Genesis {

    struct ApplicationSpecification
    {
        int Width = 300;
        int Height = Width / 16 * 10;
        int Scale = 3;
        std::string Title = "Genesis";
    };

    class Application
    {
    public:
        Application(const ApplicationSpecification& spec = ApplicationSpecification());
        ~Application();

        void Run();
        void OnUpdate();
        void OnRender();
    public:
        static Application& Get();
        static Renderer& GetRenderer() { return Get().m_Renderer; };
    private:
        void Loop();
        static void StaticLoop();
    private:
        ApplicationSpecification m_Specification;
        Renderer m_Renderer;
        std::unique_ptr<Game> m_Game;

        double m_LastTime;

        Image m_Icon;
        float m_Time = 0.0f;

    };

} // Genesis