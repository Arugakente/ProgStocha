/*********************************************
 * OPL 12.9.0.0 Model
 * Authors: G. GOSSET, Q. LASOTA, T. PICHARD, G. SCION
 * Creation Date: 31 oct. 2020 at 14:18:18
 *********************************************/

//file ending with with _subtour.dat => generated list of subtour

using CP;


int nbVertex = ...;

range Vertex = 1..nbVertex;

float c[Vertex, Vertex] = ...; //cost

tuple Subtour
{
	int len;
	{int} subtour;
}
{Subtour} Subtours = ...; //generated in another file


dvar boolean x[Vertex,Vertex]; //assignment


minimize sum(v1,v2 in Vertex) x[v1, v2] * c[v1,v2];

subject to
{
	forall (v in Vertex)
	{
		x[v,v] == 0;	 //ignores loops
	}
	
	forall(i,j in Vertex)
	{	
		x[i, j] == 0 || x[i, j] == 1;   // x(i,j) c {0,1}
	}
	
	forall(i in Vertex) sum(j in Vertex) x[i,j] == 1; //only one input and output path per vertex
	forall(j in Vertex) sum(i in Vertex) x[i,j] == 1;
	
	forall(S in Subtours) //subtour
	{    
		sum(i,j in S.subtour) x[i,j] <= S.len - 1;
	}
}