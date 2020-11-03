/*********************************************
 * OPL 12.9.0.0 Model
 * Author: Aru
 * Creation Date: 3 nov. 2020 at 10:50:26
 *********************************************/

 
int nbVertex = ...;

range Vertex = 1..nbVertex;

int Z = ...; //exact solution optimum

//float c[Vertex, Vertex] = ...; //cost
//TODO : probability version

tuple Subtour
{
	int size;
	{int} subtour;
}
{Subtour} Subtours = ...; //generated in another file


dvar boolean x[Vertex,Vertex]; //assignment


//minimize sum(v1,v2 in Vertex) x[v1, v2] * c[v1,v2];

subject to
{


}