#include "Graph.hpp"

//for debug
#include "Operators.hpp"

#include <iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
    // A LAISSER DANS LE FINAL !!!!!
    srand (time(NULL));

    Graph g = Graph("../data/ali535.tsp");
    Node n1 = Node(1,0,0);
    Node n2 = Node(2,1,1);
    printf("Distance entre les deux points n1 et n2 : %f\n", n1.calculateDistance(n2));

    for(auto const& [key1, val1] : g.getGraphListing())
    {
        cout << key1 << endl;
    }

    std::vector<std::vector<float>> test = g.getDistMat();
    for(auto current : test)
    {
        for(auto subcurrent : current)
            cout << subcurrent << " ";
        cout << endl;
    }

    auto generatedTest = randomInitialiser(g);
    for(auto current : generatedTest)
    {
        cout << current << endl;
    }
    basicScrambler(generatedTest);
    for(auto current : generatedTest)
    {
        cout << current << endl;
    }
    return 0;
}