#include "Entity.h"

#include <cmath>
#include <format>

#include "Game.h"
#include "raymath.h"

namespace Genesis {
    void Entity::OnInit(Level* level)
    {
        m_Level = level;
    }

    void Entity::Remove()
    {
        m_Level->Remove(this);
    }

    void Entity::SetPosition(int x, int y)
    {
        X = x;
        Y = y;
    }

    void Entity::UpdateLighting(const std::vector<Level::RenderTile>& lightTiles)
    {
        m_LightDist = -1;

        int lightSize = 48;
        Vector2 playerPosition = {(float)X + 8, (float)Y + 8};

        for (auto rt : lightTiles)
        {
            Vector2 lightPosition = {(float)((rt.x << 4) + 8), (float)((rt.y << 4) + 8)};
            float distance = Vector2Distance(playerPosition, lightPosition);
            if (distance > lightSize)
                continue;

            distance = Clamp(distance, 0.0f, (float)lightSize) * 2.0f;
            if (m_LightDist == -1 || distance < m_LightDist)
                m_LightDist = distance;
        }

        return;

        // ORIGINAL TECHNIQUE v
        for (int i = 0; i < lightTiles.size(); i++)
        {
            int lx0 = lightTiles[i].x << 4;
            int ly0 = lightTiles[i].y << 4;
            int lx1 = (lightTiles[i].x << 4) + 16;
            int ly1 = (lightTiles[i].y << 4) + 16;

            int cx = (lx0 + lx1) / 2;
            int cy = (ly0 + ly1) / 2;

            if (X > lx0 - lightSize && Y > ly0 - lightSize && X <  lx1 + lightSize && Y < ly1 + lightSize)
            {
                for (int y = ly0 - lightSize; y < ly1 + lightSize; y++)
                {
                    for (int x = lx0 - lightSize; x<lx1 + lightSize; x++)
                    {
                        bool b1 = (Y<ly0 - 32) && (X<lx0 - 16 || X> lx1 + 16);
                        bool b2 = (Y<ly0 - 16) && (X<lx0 - 32 || X> lx1 + 32);
                        bool b3 = (Y<ly0 + 32) && (X<lx0 - 32 || X> lx1 + 32);
                        bool b4 = (Y<ly0 + 48) && (X<lx0 - 16 || X> lx1 + 16);
                        if (b1 || b2 || b3 || b4)
                            break;

                        m_LightDist = std::sqrt(std::pow(std::abs(X - cx), 2) + std::pow(std::abs(Y - cy), 2));

                    }
                }
            }
            if (m_LightDist > 100)
                m_LightDist = -1;
        }
    }
} // Genesis
