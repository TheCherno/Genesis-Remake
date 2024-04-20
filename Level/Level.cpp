#include "Level.h"

#include "Graphics/ImageUtils.h"
#include "Application.h"

#include <unordered_map>
#include <functional>

#include "Random.h"
#include "Entity/Player.h"

namespace Genesis {
    static std::unordered_map<uint32_t, Tile*> s_TileMap = {
        {0xffffffff, &Tiles::GrassGround},
        {0xff00ff00, &Tiles::Grass},
        {0xff00FFFF, &Tiles::GrassGround},
        {0xffFFC444, &Tiles::Rock},
        {0xffff5E3A, &Tiles::Water},
        {0xffFFC2B5, &Tiles::Ice},
        {0xff04FF00, &Tiles::Flower},
        {0xff206B15, &Tiles::GrassGround}
    };

    static std::unordered_map<uint32_t, Tile*> s_TileObjectMap = {
        {0xff00FFFF, &Tiles::Torch},
        {0xff206B15, &Tiles::Tree},
    };

    Level::~Level()
    {
        delete[] m_ImageBuffer;
    }

    void Level::Load(const std::filesystem::path &path)
    {
        m_Path = path;
        m_ImageBuffer = Utils::LoadImageBuffer(path, m_Width, m_Height);

        // Randomly scatter grass
        for (int i = 0; i < m_Width * m_Height; i++)
        {
            if (m_ImageBuffer[i] == 0xffffffff)
            {
                if (Random::UInt(0, 8) == 0)
                    m_ImageBuffer[i] = 0xff00ff00;
            }
        }

        m_Player = std::make_shared<Player>(54 * 16, 23 * 16);
        Add(m_Player);
    }

    void Level::OnUpdate(float ts)
    {
        for (auto entity : m_Entities)
        {
            entity->OnUpdate(ts);
        }

        UpdateWaterSprite();
    }

    void Level::Add(std::shared_ptr<Entity> entity)
    {
        m_Entities.emplace_back(entity);
        entity->OnInit(this);
    }

    void Level::OnRender()
    {
        Renderer &renderer = Application::Get().GetRenderer();
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

                if (tile.Type == TileType::Water)
                {

                }
                renderer.RenderSprite(x << 4, y << 4, tile.Sprite);
            }
        }

        struct RenderTile
        {
            Tile tile;
            int x, y;
        };

        std::vector<RenderTile> postRender;
        std::vector<RenderTile> treeTops;

        for (int y = y0 - 3; y < y1 + 3; y++)
        {
			for (int x = x0 - 3; x < x1 + 3; x++)
            {
				const Tile& tile = GetTile2(x, y);
				if (tile.Type == TileType::Torch)
                {
					// lightTiles.add(new LightTile(x, y));
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

        for (const RenderTile& rt : postRender)
        {
            if (rt.tile.Type == TileType::Tree)
            {
                renderer.RenderSprite(rt.x << 4, (rt.y + 1) << 4,  Sprites::Tree2);
                renderer.RenderSprite((rt.x + 1) << 4, (rt.y + 1) << 4, Sprites::Tree3);
            }
            else if (rt.tile.Type == TileType::SnowTree)
            {
                renderer.RenderSprite(rt.x << 4, rt.y << 4,  Sprites::SnowTree2);
                renderer.RenderSprite((rt.x + 1) << 4, rt.y << 4, Sprites::SnowTree3);
            }
            else
            {
                renderer.RenderSprite(rt.x << 4, rt.y << 4, rt.tile.Sprite);
            }
        }

        for (auto entity : m_Entities)
        {
            entity->OnRender();
        }

        for (const RenderTile& treeTopTile : treeTops)
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

    void Level::UpdateWaterSprite()
    {
        static int waterAnim = 0;
        waterAnim++;

        Tiles::Water.Sprite = (waterAnim % 96 > 48) ? Sprites::Water2 : Sprites::Water;
    }

} // Gensis
