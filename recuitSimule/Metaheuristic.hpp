#pragma once
#include "Graph.hpp"
#include<vector>
#include<algorithm>
#include<sstream>

#include<iostream>

class Metaheuristic
{
private:
    float temperature;
    float energy;
    std::vector<const Node&> currentPath;
    std::vector<const Node&> generalBestPath;
    std::vector<const Node&> currentBestPath;
public:
    Metaheuristic();
    const std::vector<const Node&>& getCurrentPath();
    const std::vector<const Node&>& getGeneralBestPath();
    const std::vector<const Node&>& getCurrentBestPath();
    float getTemperature();
    float getEnergy();
    ~Metaheuristic();
};

Metaheuristic::~Metaheuristic()
{
}
