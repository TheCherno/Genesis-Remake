#pragma once

#include "Level/Level.h"

namespace Genesis {

    enum class EntityType
    {
        None = 0,
        Player = 1,
        Female = 2,
        ForestMob = 3,
    };

    class Entity
    {
    public:
        virtual ~Entity() = default;

        virtual void OnUpdate(float ts) {}
        virtual void OnRender() {}

        virtual EntityType GetType() const = 0;

        void OnInit(Level* level);
        void Remove();

        void SetPosition(int x, int y);
        void UpdateLighting(const std::vector<Level::RenderTile>& lightTiles);
    public:
        int X = 0, Y = 0;
    protected:
        Level* m_Level = nullptr;
        bool m_Removed = false;
        float m_LightDist = -1.0f;

    };

} // Genesis