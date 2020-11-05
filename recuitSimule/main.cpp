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

    Graph g = Graph("../data/simpleTest.tsp");

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

    auto generatedTest = randomInitialiser(g,111);
    auto generatedTest1 = randomInitialiser(g,111);
    auto generatedTest2 = randomInitialiser(g,111);

    auto generatedTest3 = randomInitialiser(g,2);
    auto generatedTest4 = randomInitialiser(g,2);
    auto generatedTest5 = randomInitialiser(g,2);

    for(auto current : generatedTest)
    {
        cout << current << endl;
    }
    cout << endl;
    for(auto current : generatedTest1)
    {
        cout << current << endl;
    }
    cout << endl;
    for(auto current : generatedTest2)
    {
        cout << current << endl;
    }
    cout << endl;
    for(auto current : generatedTest3)
    {
        cout << current << endl;
    }
    cout << endl;
    for(auto current : generatedTest4)
    {
        cout << current << endl;
    }
    cout << endl;
    for(auto current : generatedTest5)
    {
        cout << current << endl;
    }
    cout << endl;
    basicScrambler(generatedTest);
    for(auto current : generatedTest)
    {
        cout << current << endl;
    }

    Node n1 = Node(1,0,0);
    Node n2 = Node(2,1,1);
    Node n3 = Node(3,2,2);
    Node n4 = Node(4,3,3);
    printf("Distance entre les deux points n1 et n2 : %f\n", n1.calculateDistance(n2));
    cout << g.getDistanceBetweenNPoints(4, 0, 1, 2, 3) << endl;
    g.getNearestNode(2);

    return 0;
}