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
    // A LAISSER DANS LE FINAL !!!!!
    srand (time(NULL));

    if(argc != 10)
    {
        cerr << "Usage : ./main [begin temperature] [end temperature] [temperature evolution factor] [standard deviation factor] [dataInput] [outputFileName*] [init method**] [scramble method***] [real time exoprt]" << endl;
        cerr << "*no extention for output file (added automatically)" << endl;
        cerr << "**0 random , 1 glouton" << endl;
        cerr << "***0 random exchange , 1 multiple random exchange, 2 3pack echanges" << endl;
        cerr << "****0 export unique a la fin du programme , 1 export " << endl;
        return 1;
    }

    float beginTemp = stof(argv[1]);
    float endTemp = stof(argv[2]);
    float evolutionFactor = stof(argv[3]);
    float stdDeviationFactor = stof(argv[4]);
    string dataInput = argv[5];
    string valueOutput = argv[6];
    valueOutput+=".csv";
    int initialiser = stoi(argv[7]);
    int randomisationMethod = stoi(argv[8]);
    int RTexport = stoi(argv[9]);

    Graph g(dataInput,stdDeviationFactor);

    void (*randomiser)(std::vector<long>&) ;
    std::vector<long> (*initialBuilder)(Graph&,long) ;

    cout << "starting in ";
    switch (initialiser)
    {
        case 0:
            cout << "random ";
            initialBuilder = randomInitialiser;
        break;
        case 1:
            cout << "glouton ";
            initialBuilder = gloutonInitialiser;
        break;
    }

    cout << "with ";
    switch (randomisationMethod)
    {
        case 0:
            cout << "basic scrambler ";
            randomiser = basicScrambler;
        break;
        case 1:
            cout << "multiple scrambler ";
            randomiser = multipleScramble;
        break;
        case 2:
            cout << "stack scrambler ";
            randomiser = stackScramble;
        break;
    }
    cout << endl;

    Metaheuristic meta(beginTemp,endTemp,evolutionFactor,g,randomiser,initialBuilder,valueOutput,RTexport==1);

    meta.solve();
    vector<long> result = meta.getGeneralBestPath();
    for(auto current : result)
        cout << current << " " ;
    cout << endl;
    cout << meta.getBestMeanEnergy() << endl;
    if(RTexport == 0)
    {
        meta.exportData();
    }
    return 0;
}