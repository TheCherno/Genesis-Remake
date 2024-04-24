#pragma once

#include <random>

#include "raylib.h"

namespace Genesis {

    class Random
    {
    public:
        static void Init()
        {
            s_RandomEngine.seed(std::random_device()());
        }

        static uint32_t UInt()
        {
            return s_Distribution(s_RandomEngine);
        }

        static uint32_t UInt(uint32_t max)
        {
            return s_Distribution(s_RandomEngine) % (max + 1);
        }

        static int Int(uint32_t max)
        {
            return (int)UInt(max);
        }

        static uint32_t UInt(uint32_t min, uint32_t max)
        {
            return min + (s_Distribution(s_RandomEngine) % (max - min + 1));
        }

        static float Float()
        {
            return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
        }

        static Vector2 Vec2()
        {
            return Vector2{ Float(), Float() };
        }

        static Vector2 Vec2(float min, float max)
        {
            return Vector2{ Float() * (max - min) + min, Float() * (max - min) + min };
        }
    private:
        inline static std::mt19937 s_RandomEngine;
        inline static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
    };

} // Genesis