#pragma once

#include <string>

#include "Renderer.h"

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

    public:
        static Application& Get();
        static Renderer& GetRenderer() { return Get().m_Renderer; };
    private:
        ApplicationSpecification m_Specification;
        Renderer m_Renderer;

    };

} // Genesis