#include "Graph.hpp"

int main()
{
    Graph("../data/ali535.tsp");
    Node n1 = Node(1,0,0);
    Node n2 = Node(2,1,1);
    printf("Distance entre les deux points n1 et n2 : %f\n", n1.calculateDistance(n2));
    return 0;
}