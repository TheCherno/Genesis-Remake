#pragma once
#include <filesystem>
#include <vector>

#include "Graphics/Sprite.h"

#include "Tile.h"

namespace Genesis {

    class Player;

    class Entity;

    class Level
    {
    public:
        Level() = default;
        ~Level();

        void Add(std::shared_ptr<Entity> entity);
        void Load(const std::filesystem::path& path);

        void OnUpdate(float ts);
        void OnRender();

        const Tile& GetTile(int x, int y);
        const Tile& GetTile2(int x, int y);

        void Remove(Entity* entity);
    private:
        void UpdateWaterSprite();
    private:
        std::filesystem::path m_Path;
        uint32_t* m_ImageBuffer = nullptr;
        uint32_t m_Width = 0, m_Height = 0;

        std::vector<std::shared_ptr<Entity>> m_Entities;
        std::shared_ptr<Player> m_Player;
    };

} // Gensis