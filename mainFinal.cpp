#include "Graph.hpp"

//for debug
#include "Operators.hpp"
#include "Metaheuristic.hpp"
#include <iostream>
#include<ctime>
#include<cstdlib>
#include<string>

using namespace std;

int main(int argc,char** argv)
{
    float beginTemp;
    float endTemp;
    float evolutionFactor;
    float stdDeviationFactor;
    string dataInput;
    string valueOutput;
    int initialiser;
    int randomisationMethod;

    Graph g(dataInput,stdDeviationFactor);

    Metaheuristic a(beginTemp,endTemp,evolutionFactor,g,basicScrambler,randomInitialiser,valueOutput);
    // A LAISSER DANS LE FINAL !!!!!
    srand (time(NULL));

    return 0;
}