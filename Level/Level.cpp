#include "Level.h"

#include <format>

#include "Graphics/ImageUtils.h"
#include "Application.h"

#include <unordered_map>
#include <functional>

#include "Random.h"
#include "Entity/Female.h"
#include "Entity/Player.h"
#include "Menu/GameOverMenu.h"
#include "Utils/Utils.h"

namespace Genesis {
    static std::unordered_map<uint32_t, Tile *> s_TileMap = {
        {0xffffffff, &Tiles::GrassGround},
        {0xff00ff00, &Tiles::Grass},
        {0xff00FFFF, &Tiles::GrassGround},
        {0xffFFC444, &Tiles::Rock},
        {0xffff5E3A, &Tiles::Water},
        {0xffFFC2B5, &Tiles::Ice},
        {0xff04FF00, &Tiles::Flower},
        {0xff206B15, &Tiles::GrassGround}
    };

    static std::unordered_map<uint32_t, Tile *> s_TileObjectMap = {
        {0xff00FFFF, &Tiles::Torch},
        {0xff206B15, &Tiles::Tree},
    };

    Level::Level(Game& game)
        : m_Game(game), m_Population(*this)
    {
    }

    Level::~Level()
    {
        delete[] m_ImageBuffer;
    }

    void Level::Load(const std::filesystem::path& path)
    {
        // Reset
        m_Entities.clear();
        m_Time = 0;
        Brightness = 0;
        m_BrightnessDelta = 1;
        m_Population.Reset();

        delete[] m_ImageBuffer;
        m_ImageBuffer = nullptr;

        std::filesystem::path finalPath = Genesis::Utils::ResolvePath(path);

        m_Path = finalPath;
        m_ImageBuffer = Utils::LoadImageBuffer(finalPath, m_Width, m_Height);
        ResetTimer();

        // Randomly scatter grass
        for (int i = 0; i < m_Width * m_Height; i++)
        {
            if (m_ImageBuffer[i] == 0xffffffff)
            {
                if (Random::UInt(0, 8) == 0)
                    m_ImageBuffer[i] = 0xff00ff00;
            }
        }
    }

    void Level::OnUpdate(float ts)
    {
        m_Time++;
        if (m_Time % 50 == 0)
            Time();

        //for (auto entity : m_Entities)
        for (size_t i = 0; i < m_Entities.size(); i++)
        {
            m_Entities[i]->OnUpdate(ts);
        }

        if (Play)
        {
            m_Player->OnUpdate(ts);
            m_Population.OnUpdate(ts);
        }

        UpdateWaterSprite();
    }

    void Level::Add(std::shared_ptr<Entity> entity)
    {
        m_Entities.emplace_back(entity);
        entity->OnInit(this);
    }

    void Level::AddPlayer(std::shared_ptr<Player> player)
    {
        m_Player = player;
        m_Player->OnInit(this);
    }

    void Level::OnRender()
    {
        Renderer& renderer = Application::GetRenderer();
        ASSERT(m_Player);

        int viewportWidth = renderer.GetWidth();
        int viewportHeight = renderer.GetHeight();

        int vx = m_Player->X - viewportWidth / 2;
        int vy = m_Player->Y - viewportHeight / 2;

        renderer.SetViewOffset(vx, vy);

        const int x0 = vx >> 4;
        const int x1 = (vx + viewportWidth + 15) >> 4;
        const int y0 = vy >> 4;
        const int y1 = (vy + viewportHeight + 15) >> 4;
        for (int y = y0; y < y1; y++)
        {
            for (int x = x0; x < x1; x++)
            {
                const Tile& tile = GetTile(x, y);
                renderer.RenderSprite(x << 4, y << 4, tile.Sprite);
            }
        }

        std::vector<RenderTile> postRender;
        std::vector<RenderTile> lightTiles;
        std::vector<RenderTile> lightEmissionTiles;
        std::vector<RenderTile> treeTops;

        for (int y = y0 - 3; y < y1 + 3; y++)
        {
            for (int x = x0 - 3; x < x1 + 3; x++)
            {
                const Tile& tile = GetTile2(x, y);
                if (tile.Type == TileType::Torch)
                {
                    lightTiles.emplace_back(RenderTile{Tiles::Torch, x, y});
                    lightEmissionTiles.emplace_back(RenderTile{Tiles::Torch, x, y});
                    postRender.emplace_back(RenderTile{Tiles::Torch, x, y});
                }
                else if (tile.Type == TileType::Tree)
                {
                    postRender.emplace_back(RenderTile{Tiles::Tree, x, y});
                    treeTops.emplace_back(RenderTile{Tiles::TreeTop, x, y});
                }
                else if (tile.Type == TileType::SnowTree)
                {
                    postRender.emplace_back(RenderTile{Tiles::SnowTree, x, y});
                    treeTops.emplace_back(RenderTile{Tiles::SnowTreeTop, x, y});
                }
            }
        }

        for (const RenderTile& rt: lightTiles)
        {
            RenderLightTile(rt.x, rt.y);
        }

        for (const RenderTile& rt: postRender)
        {
            if (rt.tile.Type == TileType::Tree)
            {
                renderer.RenderSprite(rt.x << 4, (rt.y + 1) << 4, Sprites::Tree2);
                renderer.RenderSprite((rt.x + 1) << 4, (rt.y + 1) << 4, Sprites::Tree3);
            } else if (rt.tile.Type == TileType::SnowTree)
            {
                renderer.RenderSprite(rt.x << 4, rt.y << 4, Sprites::SnowTree2);
                renderer.RenderSprite((rt.x + 1) << 4, rt.y << 4, Sprites::SnowTree3);
            } else
            {
                renderer.RenderSprite(rt.x << 4, rt.y << 4, rt.tile.Sprite);
            }
        }

        for (auto entity : m_Entities)
        {
            entity->UpdateLighting(lightEmissionTiles); // NOTE(Yan): lightTiles for orig technique
            entity->OnRender();
        }

        if (Play)
        {
            m_Player->UpdateLighting(lightEmissionTiles);
            m_Player->OnRender();
        }

        for (const RenderTile& treeTopTile: treeTops)
        {
            renderer.RenderSprite(treeTopTile.x << 4, treeTopTile.y << 4,
                                  treeTopTile.tile.Type == TileType::SnowTree ? Sprites::SnowTree0 : Sprites::Tree0);
            renderer.RenderSprite((treeTopTile.x + 1) << 4, treeTopTile.y << 4,
                                  treeTopTile.tile.Type == TileType::SnowTree ? Sprites::SnowTree1 : Sprites::Tree1);
        }
    }

    const Tile& Level::GetTile(int x, int y)
    {
        if (x < 0 || y < 0 || x >= m_Width || y >= m_Height)
            return Tiles::GrassGround;

        int tileColor = m_ImageBuffer[x + y * m_Width];
        if (!s_TileMap.contains(tileColor))
            return Tiles::GrassGround;

        return *s_TileMap.at(tileColor);
    }

    const Tile& Level::GetTile2(int x, int y)
    {
        if (x < 0 || y < 0 || x >= m_Width || y >= m_Height)
            return Tiles::GrassGround;

        int tileColor = m_ImageBuffer[x + y * m_Width];
        if (!s_TileObjectMap.contains(tileColor))
            return Tiles::GrassGround;

        return *s_TileObjectMap.at(tileColor);
    }

    void Level::Remove(Entity* entity)
    {
    }

    std::vector<std::shared_ptr<Female> > Level::GetBreedableFemaleEntities() const
    {
        std::vector<std::shared_ptr<Female> > females;
        for (const auto& entity: m_Entities)
        {
            if (entity->GetType() == EntityType::Female)
            {
                auto female = std::static_pointer_cast<Female>(entity);
                if (female->CanSpawnChild)
                    females.emplace_back(female);
            }
        }
        return females;
    }

    void Level::Time()
    {
        if (Brightness < -200)
            m_BrightnessDelta = 1;
        else if (Brightness > 20)
            m_BrightnessDelta = -1;

        Brightness += m_BrightnessDelta;
    }

    void Level::UpdateWaterSprite()
    {
        static int waterAnim = 0;
        waterAnim++;

        Tiles::Water.Sprite = (waterAnim % 96 > 48) ? Sprites::Water2 : Sprites::Water;
    }

    void Level::RenderLightTile(int x, int y)
    {
        int tb = Brightness;
        if (tb < -240)
            tb = -240;
        if (tb > 0)
            tb = 0;

        Renderer& renderer = Application::GetRenderer();

        Tile tile;
        for (int yy = -3; yy <= 3; yy++)
        {
            for (int xx = -3; xx <= 3; xx++)
            {
                for (int i = 0; i < 4; i++)
                {
                    int xt = ((x << 4) + (i % 2 * 2 - 1) * 7) >> 4;
                    int yt = ((y << 4) + (i / 2 * 2 - 1) * 7) >> 4;
                    tile = GetTile(xt + xx, yt + yy);
                }
                int xTile = x * 16 + xx * 16;
                int yTile = y * 16 + yy * 16;
                double r = std::abs((std::pow(xx * PI, 2)) + std::abs(std::pow(yy * PI, 2)));
                double intensity = r * tb * 0.00012;
                if (r < 100)
                    renderer.RenderLight(xTile, yTile, tile.Sprite, 62, 64, 65, intensity);
            }
        }
    }

    void Level::ResetTimer()
    {
        m_TimerMin = 5;
        m_TimerSec = 0;

        UpdateTimer();
    }

    void Level::UpdateTimer()
    {
        m_TimerString = std::format("{}:{}", m_TimerMin, m_TimerSec);
        if (m_TimerSec == 0 && m_TimerMin != 0)
            m_TimerString = std::format("{}:00", m_TimerMin);
        if (m_TimerSec < 10)
            m_TimerString = std::format("{}:0{}", m_TimerMin, m_TimerSec);
        if (m_TimerSec <= 0 && m_TimerMin != 0)
        {
            m_TimerSec = 60;
            m_TimerMin--;
        }

        if (m_TimerSec <= 0 && m_TimerMin <= 0 && Play)
        {
            Play = false;
            m_Game.SetMenu<GameOverMenu>();
        }
        m_TimerSec--;
    }

    void Level::RenderUI()
    {
        if (Play)
        {
            RenderTimer();
            m_Population.OnRender();
        }
    }

    void Level::RenderTimer()
    {
        int col = 0xffffffff;
        //if (Game.level instanceof SnowLevel) col = 0;

        Renderer& renderer = Application::GetRenderer();
        renderer.RenderText(m_TimerString, 430, 495, 30, 1, col);
    }
} // Gensis
