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

    for(int i =0 ; i<g.getGraphListing().size();i++)
    {
        cout << i << " " <<g[i].getLogicalNumber() << endl;
    }

    std::vector<std::vector<float>> test = g.getDistMat();
    for(auto current : test)
    {
        for(auto subcurrent : current)
            cout << subcurrent << "\t";
        cout << endl;
    }

    /*
    Node n1 = Node(1,0,0);
    Node n2 = Node(2,1,1);
    Node n3 = Node(3,2,2);
    Node n4 = Node(4,3,3);
    printf("Distance entre les deux points n1 et n2 : %f\n", n1.calculateDistance(n2));
    cout << g.getDistanceBetweenNPoints(4, 0, 1, 2, 3) << endl;
    cout << "------------" << endl;
    g.getNearestNode(0);
    g.getNearestNode(1);
    g.getNearestNode(2);
    g.getNearestNode(3);
    g.getNearestNode(4);
    g.getNearestNode(5);
    g.getNearestNode(6);
    g.getNearestNode(7);
    g.getNearestNode(8);
    g.getNearestNode(9);
    */

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

    return 0;
}