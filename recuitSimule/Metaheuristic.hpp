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
    std::vector<long> currentPath;
    std::vector<long> generalBestPath;
    std::vector<long> currentBestPath;
public:
    Metaheuristic();
    const std::vector<long>& getCurrentPath();
    const std::vector<long>& getGeneralBestPath();
    const std::vector<long>& getCurrentBestPath();
    std::vector<long> solve();
    float getTemperature();
    float getEnergy();
    ~Metaheuristic(){};
};