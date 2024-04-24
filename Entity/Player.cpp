#include "Player.h"

#include "Application.h"
#include "Graphics/Renderer.h"
#include "Female.h"
#include "ForestMob.h"
#include "Random.h"
#include "Sound/Sound.h"

namespace Genesis {
    Player::Player(int x, int y)
    {
        X = x;
        Y = y;
    }

    void Player::OnUpdate(float ts)
    {
        int xa = 0, ya = 0;

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
            ya--;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
            ya++;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
            xa--;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
            xa++;

        m_Walking = false;
        if (xa != 0 || ya != 0)
        {
            Move(xa, ya);
            m_Walking = true;
        }

        if (IsKeyDown(KEY_ESCAPE))
        {
            // back to main menu
        }

        CheckFemaleCollision();
    }

    void Player::UpdateSprite()
    {
        m_Anim++;

        if (m_Dir == 0)
        {
            m_Sprite = Sprites::Player0;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                m_Sprite = Sprites::Player1;
                if (m_Anim % 30 > 15)
                {
                    m_SpriteFlip = 0;
                } else
                {
                    m_SpriteFlip = 1;
                }
            }
        }
        if (m_Dir == 1)
        {
            m_Sprite = Sprites::Player4;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                if (m_Anim % 30 > 15)
                {
                    m_Sprite = Sprites::Player4;
                } else
                {
                    m_Sprite = Sprites::Player5;
                }
            }
        }
        if (m_Dir == 2)
        {
            m_Sprite = Sprites::Player2;
            m_SpriteFlip = 0;
            if (m_Walking)
            {
                m_Sprite = Sprites::Player3;
                if (m_Anim % 30 > 15)
                {
                    m_SpriteFlip = 0;
                } else
                {
                    m_SpriteFlip = 1;
                }
            }
        }
        if (m_Dir == 3)
        {
            m_Sprite = Sprites::Player4;
            m_SpriteFlip = 1;
            if (m_Walking)
            {
                if (m_Anim % 30 > 15)
                {
                    m_Sprite = Sprites::Player4;
                } else
                {
                    m_Sprite = Sprites::Player5;
                }
            }
        }
    }

    void Player::CheckFemaleCollision()
    {
        auto females = m_Level->GetBreedableFemaleEntities();

        for (auto female: females)
        {
            if ((X >> 4) == (female->X >> 4) && (Y >> 4) == (female->Y >> 4))
            {
                int spawnCount = Random::Int(3) + 1;
                for (int c = 0; c < spawnCount; c++)
                {
                    Sounds::Breed.Play();
                    m_Level->Add(std::make_shared<ForestMob>(X, Y));
                }
                Population::Growth += (Population::Growth / 4);
                female->CanSpawnChild = false;
                //if (level instanceof OceanLevel)
                {
                    spawnCount = Random::Int(1) + 1;
                    for (int fe = 0; fe < spawnCount; fe++)
                    {
                        auto[sx, sy] = GenerateFemaleSpawn();
                        m_Level->Add(std::make_shared<Female>(sx, sy));
                    }
                }
                /*else if (level instanceof SnowLevel)
                {
                    for (int fe = 0; fe < random.nextInt(5) + 2; fe++)
                    {
                        Entity f = new Female();
                        f.x = spawnFemale().x;
                        f.y = spawnFemale().y;
                        level.add(f, level);
                    }
                } else
                {
                    for (int fe = 0; fe < random.nextInt(4) + 1; fe++)
                    {
                        Entity f = new Female();
                        f.x = spawnFemale().x;
                        f.y = spawnFemale().y;
                        level.add(f, level);
                    }
                }*/
            }
        }
    }

    std::pair<int, int> Player::GenerateFemaleSpawn()
    {
        int fx = 0;
        int fy = 0;
        int ran = Random::Int(1);
        if (ran == 0)
        {
            /*if (level instanceof ForestLevel)
            {
                fx = random.nextInt(128 * 16);
                fy = 41 * 16;
            }*/
            //if (level instanceof OceanLevel)
            {
                fx = Random::Int(41) + 38;
                fy = Random::Int(4) + 76;
            }
            /*if (level instanceof SnowLevel)
            {
                fx = random.nextInt(14) + 27;
                fy = random.nextInt(23) + 12;
            }*/
        }
        if (ran == 1)
        {
            /*if (level instanceof ForestLevel)
            {
                fx = 103 * 16;
                fy = random.nextInt(128 * 16);
            }*/
            //if (level instanceof OceanLevel)
            {
                fx = Random::Int(21) + 43;
                fy = Random::Int(13) + 57;
            }
            /*
            if (level instanceof SnowLevel)
            {
                fx = random.nextInt(44) + 62;
                fy = random.nextInt(18) + 95;
            }*/
        }
        return { fx << 4, fy << 4 };
    }
} // Genesis
