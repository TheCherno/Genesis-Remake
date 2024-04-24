#pragma once

namespace Genesis {

    class Menu
    {
    public:
        virtual ~Menu() = default;

        virtual void OnUpdate(float ts) {}
        virtual void OnRender() {}
    };

} // Genesis