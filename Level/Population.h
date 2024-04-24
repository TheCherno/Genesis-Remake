#pragma once

namespace Genesis {
    class Level;

    class Population
    {
    public:
        Population(Level& level);

        void OnUpdate(float ts);
        void OnRender();

        void Reset();
    public:
        inline static double PopulationCount = 2.0;
        inline static double Growth = 0.05;
    private:
        Level& m_Level;

    };

} // Genesis