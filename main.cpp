#include "Graph.hpp"

//for debug
#include "Operators.hpp"
#include "Metaheuristic.hpp"
#include <iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
    // A LAISSER DANS LE FINAL !!!!!
    srand (time(NULL));

    Graph g("../data/berlin52.tsp",0.025f);

/*
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

    Node n1 = Node(1,0,0);
    Node n2 = Node(2,1,1);
    Node n3 = Node(3,2,2);
    Node n4 = Node(4,3,3);
    printf("Distance entre les deux points n1 et n2 : %f\n", n1.calculateDistance(n2));
    cout << g.getDistanceBetweenNPoints(4, 0, 1, 2, 3) << endl;
    cout << "------------" << endl;
    cout << "nearest node for 0 " << g.getNearestNode(0) << endl;
    cout << "nearest node for 1 " << g.getNearestNode(1) << endl;
    cout << "nearest node for 2 " << g.getNearestNode(2) << endl;
    cout << "nearest node for 3 " << g.getNearestNode(3) << endl;
    cout << "nearest node for 4 " << g.getNearestNode(4) << endl;
    cout << "nearest node for 5 " << g.getNearestNode(5) << endl;
    cout << "nearest node for 6 " << g.getNearestNode(6) << endl;
    cout << "nearest node for 7 " << g.getNearestNode(7) << endl;
    cout << "nearest node for 8 " << g.getNearestNode(8) << endl;
    cout << "nearest node for 9 " << g.getNearestNode(9) << endl;

    auto generatedTest = randomInitialiser(g,111);
    g.reinitTaken();
    auto generatedTest1 = randomInitialiser(g,111);
    g.reinitTaken();
    auto generatedTest2 = randomInitialiser(g,111);
    g.reinitTaken();

    auto generatedTest3 = randomInitialiser(g,2);
    g.reinitTaken();
    auto generatedTest4 = randomInitialiser(g,2);
    g.reinitTaken();
    auto generatedTest5 = randomInitialiser(g,2);
    g.reinitTaken();
    auto generatedTest6 = gloutonInitialiser(g,0);
    g.reinitTaken();
    auto generatedTest7 = gloutonInitialiser(g,8);
    g.reinitTaken();
    auto generatedTest8 = gloutonInitialiser(g,9);
    g.reinitTaken();

    for(auto current : generatedTest)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest1)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest2)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest3)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest4)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest5)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest6)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest7)
    {
        cout << current << " ";
    }
    cout << endl;
    for(auto current : generatedTest8)
    {
        cout << current << " ";
    }
    cout << endl;
    basicScrambler(generatedTest);
    for(auto current : generatedTest)
    {
        cout << current << " ";
    }
    cout << endl;
*/
    Metaheuristic a((float)(500.0),(float)(0.05),0.99999,g,basicScrambler,randomInitialiser,"./basic_rand.csv",false);
    Metaheuristic b((float)(500.0),(float)(0.05),0.99999,g,basicScrambler,gloutonInitialiser,"./basic_glouton.csv",false);
    Metaheuristic c((float)(500.0),(float)(0.05),0.99999,g,multipleScramble,randomInitialiser,"./multi_rand.csv",false);
    Metaheuristic d((float)(500.0),(float)(0.05),0.99999,g,multipleScramble,gloutonInitialiser,"./multi_glouton.csv",false);
    Metaheuristic e((float)(500.0),(float)(0.05),0.99999,g,stackScramble,randomInitialiser,"./stack_rand.csv",false);
    Metaheuristic f((float)(500.0),(float)(0.05),0.99999,g,stackScramble,gloutonInitialiser,"./stack_glouton.csv",false);

    cout << "test random" << endl;
    vector<long> test1 = a.solve();
    g.reinitTaken();
    cout << "test glouton" << endl;
    vector<long> test2 = b.solve();
    g.reinitTaken();
    cout << "test random multi" << endl;
    vector<long> test3 = c.solve();
    g.reinitTaken();
    cout << "test glouton multi" << endl;
    vector<long> test4 = d.solve();
    g.reinitTaken();
    cout << "test random stack" << endl;
    vector<long> test5 = e.solve();
    g.reinitTaken();
    cout << "test glouton stack" << endl;
    vector<long> test6 = f.solve();

    for(auto current : test1)
    {
        cout << current << " ";
    }
    cout << a.getBestMeanEnergy() << endl;
    cout << endl;

    for(auto current : test2)
    {
        cout << current << " ";
    }
    cout << b.getBestMeanEnergy() << endl;
    cout << endl;

    for(auto current : test3)
    {
        cout << current << " ";
    }
    cout << c.getBestMeanEnergy() << endl;
    cout << endl;

    for(auto current : test4)
    {
        cout << current << " ";
    }
    cout << d.getBestMeanEnergy() << endl;
    cout << endl;


    for(auto current : test5)
    {
        cout << current << " ";
    }
    cout << e.getBestMeanEnergy() << endl;
    cout << endl;


    for(auto current : test6)
    {
        cout << current << " ";
    }
    cout << f.getBestMeanEnergy() << endl;

    a.exportData();
    b.exportData();
    c.exportData();
    d.exportData();
    e.exportData();
    f.exportData();

    return 0;
}