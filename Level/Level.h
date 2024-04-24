#pragma once
#include <filesystem>
#include <vector>

#include "Graphics/Sprite.h"

#include "Tile.h"

namespace Genesis {
    class Female;

    class Player;

    class Entity;

    class Level
    {
    public:
        using EntityList = std::vector<std::shared_ptr<Entity>>;

        struct RenderTile
        {
            Tile tile;
            int x, y;
        };
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

        const EntityList& GetEntities() const { return m_Entities; }
        std::vector<std::shared_ptr<Female>> GetBreedableFemaleEntities() const;

        void Time();

        void UpdateTimer();
        void RenderTimer();
    private:
        void UpdateWaterSprite();
        void RenderLightTile(int x, int y);
    public:
        bool Play = false;
        inline static int Brightness = 0;
    private:
        std::filesystem::path m_Path;
        uint32_t* m_ImageBuffer = nullptr;
        uint32_t m_Width = 0, m_Height = 0;

        EntityList m_Entities;
        std::shared_ptr<Player> m_Player;

        int m_Time = 0;
        int m_BrightnessDelta = 1;

        // Game timer
        int m_TimerMin = 5;
        int m_TimerSec = 0;
        std::string m_TimerString;
    };

} // Gensis