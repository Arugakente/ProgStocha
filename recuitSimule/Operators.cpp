#include "Operators.hpp"

using namespace std;

vector<long> randomInitialiser(Graph& usedGraph,long departureId = -1)
{
    vector<long> generatedSol;
    if(departureId != -1)
    {
        generatedSol.push_back(departureId);
        usedGraph.setTaken(departureId);
    }

    for(auto const& [key1, val1] : usedGraph.getGraphListing())
    {
        if(key1 != departureId)
        {
            generatedSol.push_back(key1);
            usedGraph.setTaken(key1);
        }
    }
    shuffle(generatedSol.begin(),generatedSol.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    return generatedSol;
}

vector<long> gloutonInitialiser(Graph& usedGraph,long departureId = -1)
{
    vector<long> generatedSol;
    
    if(departureId != -1)
    {
        generatedSol.push_back(departureId);
        usedGraph.setTaken(departureId);
    }

    if(departureId != -1)
        generatedSol.push_back(departureId);

    while(generatedSol.size() < usedGraph.getGraphDim())
    {
        generatedSol.push_back(usedGraph.getNearestNode(generatedSol.back()));
    }

    return generatedSol;
}


void basicScrambler(vector<long>& toScramble)
{
    if(toScramble.size() > 1)
    {
        int permuted1 = rand()%toScramble.size();
        int permuted2 = rand()%toScramble.size();

        while(permuted2 == permuted1)
        {
            int permuted2 = rand()%toScramble.size();
        }
        long tmp = toScramble[permuted1];
        toScramble[permuted1] = toScramble[permuted2];
        toScramble[permuted2] = tmp;
    }
}