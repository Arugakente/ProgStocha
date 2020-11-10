#include<vector>
#include<algorithm>
#include <random>
#include <chrono>
#include"Graph.hpp"

#include<ctime>
#include<cstdlib>


std::vector<long> randomInitialiser(Graph& usedGraph,long departureId = -1);
std::vector<long> gloutonInitialiser(Graph& usedGraph,long departureId = -1);
void basicScrambler(std::vector<long>& toScramble);
void multipleScramble(std::vector<long>& toScramble);