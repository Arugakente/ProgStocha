/*********************************************
 * OPL 12.9.0.0 Model
 * Author: Aru
 * Creation Date: 7 nov. 2020 at 13:53:54
 *********************************************/
 
int nbVertex = ...;
range Vertex = 1..nbVertex;

float c[Vertex, Vertex] = ...; //cost

dvar boolean x[Vertex,Vertex]; //assignment
dvar int u[2..nbVertex];


minimize sum(v1,v2 in Vertex) x[v1, v2] * c[v1,v2];

subject to
{
	forall (v in Vertex)
	{
		x[v,v] == 0;	 //ignores loops
	}
	
	forall(i,j in Vertex)
	{	
		x[i,j] == 0 || x[i,j] == 1;   // x(i,j) c {0,1}
	}
	
	forall(i in Vertex) sum(j in Vertex) x[i,j] == 1; //only one input and output path per vertex
	forall(j in Vertex) sum(i in Vertex) x[i,j] == 1;
	
	//MTZ contraints
	forall(i,j in 2..nbVertex)
	{
		if (i!=j) u[i] - u[j] + nbVertex * x[i,j] <= nbVertex-1;
	}
	
	forall(i in 2..nbVertex) u[i] >= 1 && u[i] <= nbVertex-1;
	
	
	
}