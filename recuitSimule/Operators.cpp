#include "Operators.hpp"

using namespace std;

vector<long> randomInitialiser(const Graph& usedGraph)
{
    vector<long> generatedSol;
    for(auto const& [key1, val1] : usedGraph.getGraphListing())
    {
        generatedSol.push_back(key1);
    }
    shuffle(generatedSol.begin(),generatedSol.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    return generatedSol;
}

vector<long> gloutonInitialiser(const Graph& usedGraph)
{

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