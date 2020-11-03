#include<vector>
#include<algorithm>
#include <random>
#include <chrono>
#include"Graph.hpp"

#include<ctime>
#include<cstdlib>


std::vector<long> randomInitialiser(const Graph& usedGraph);
std::vector<long> gloutonInitialiser(const Graph& usedGraph);
void basicScrambler(std::vector<long>& toScramble);