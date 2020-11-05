#include "Operators.hpp"

using namespace std;

vector<long> randomInitialiser(Graph& usedGraph,long departureId)
{
    vector<long> generatedSol;
    bool offset = false;
    if(departureId >= 0 && departureId < usedGraph.getGraphListing().size())
    {
        generatedSol.push_back(departureId);
        usedGraph.setTaken(departureId);
        offset = true;
    }

    for(int i = 0 ; i<usedGraph.getGraphListing().size();i++)
    {
        if(i != departureId)
        {
            generatedSol.push_back(i);
            usedGraph.setTaken(i);
        }
    }
    shuffle(offset?generatedSol.begin()+1:generatedSol.begin(),generatedSol.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    return generatedSol;
}

vector<long> gloutonInitialiser(Graph& usedGraph,long departureId)
{
    vector<long> generatedSol;

    if(departureId >= 0 && departureId < usedGraph.getGraphListing().size())
    {
        generatedSol.push_back(departureId);
        usedGraph.setTaken(departureId);
    }
    else
    {
        long selected = rand()%usedGraph.getGraphDim();
        //if no start point defined : random in graph
         generatedSol.push_back(selected);
         usedGraph.setTaken(selected);
    }

    while(generatedSol.size() < usedGraph.getGraphDim())
    {
        long selected = usedGraph.getNearestNode(generatedSol.back());
        generatedSol.push_back(selected);
        usedGraph.setTaken(selected);
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
            permuted2 = rand()%toScramble.size();
        }
        long tmp = toScramble[permuted1];
        toScramble[permuted1] = toScramble[permuted2];
        toScramble[permuted2] = tmp;
    }
}