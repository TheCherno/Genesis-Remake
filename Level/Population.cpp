#include "Population.h"

#include <cmath>
#include <cstdint>
#include <format>

#include "Application.h"
#include "Level.h"
#include "Random.h"
#include "Entity/ForestMob.h"
#include "Graphics/Renderer.h"

namespace Genesis {

    Population::Population(Level& level)
        : m_Level(level)
    {
    }

    void Population::OnUpdate(float ts)
    {
        uint64_t pop = (uint64_t)std::floor(PopulationCount);
        if (m_Level.Play)
            PopulationCount += Growth;

        if (pop % 800 == 0)  // TODO(Yan): super sus
        {
            //if (level instanceof ForestLevel) level.add(new ForestMob());
            /*if (level instanceof OceanLevel)*/
            {
                int x = Random::Int(20 * 16 - 1) + 54 * 16;
                int y = 23 * 16;
                m_Level.Add(std::make_shared<ForestMob>(x, y));
            }
            /*if (level instanceof ForestLevel && random.nextInt(5) == 0) {
                level.add(new Female());
                population++;
            }*/
        }
    }

    void Population::OnRender()
    {
        uint64_t pop = (uint64_t)std::floor(PopulationCount);
        std::string populationDisplay = std::format("Population: {}", pop);
        int textLength = (int) (populationDisplay.length() * 17.7);
        int col = 0xffffffff;
        // if (Game.level instanceof SnowLevel) col = 0;
        //screen.renderText(populationDisplay, 900 - textLength, 30, 30, 0, col);

        Renderer& renderer = Application::GetRenderer();
        renderer.RenderText(populationDisplay, 950 - textLength, 10, 30, 1, col);
    }

    void Population::Reset()
    {
        PopulationCount = 2.0;
        Growth = 0.05;
    }
} // Genesis