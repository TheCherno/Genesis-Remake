#pragma once
#include <filesystem>
#include <vector>

#include "Population.h"
#include "Graphics/Sprite.h"

#include "Tile.h"

namespace Genesis {
    class Game;
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
        Level(Game& game);
        ~Level();

        void Add(std::shared_ptr<Entity> entity);
        void AddPlayer(std::shared_ptr<Player> player);

        void Load(const std::filesystem::path& path);

        std::shared_ptr<Player> GetPlayer() const { return m_Player;}

        void OnUpdate(float ts);
        void OnRender();

        const Tile& GetTile(int x, int y);
        const Tile& GetTile2(int x, int y);

        void Remove(Entity* entity);

        const EntityList& GetEntities() const { return m_Entities; }
        std::vector<std::shared_ptr<Female>> GetBreedableFemaleEntities() const;

        void Time();

        void UpdateTimer();
        void RenderUI();
    private:
        void UpdateWaterSprite();
        void RenderLightTile(int x, int y);
        void RenderTimer();

        void ResetTimer();
    public:
        bool Play = false;
        inline static int Brightness = 0;
    private:
        Game& m_Game;
        std::filesystem::path m_Path;
        uint32_t* m_ImageBuffer = nullptr;
        uint32_t m_Width = 0, m_Height = 0;

        EntityList m_Entities;
        std::shared_ptr<Player> m_Player;
        Population m_Population;

        int m_Time = 0;
        int m_BrightnessDelta = 1;

        // Game timer
        int m_TimerMin = 5;
        int m_TimerSec = 0;
        std::string m_TimerString;
    };

} // Gensis