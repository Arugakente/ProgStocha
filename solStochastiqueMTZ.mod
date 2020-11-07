/*********************************************
 * OPL 12.9.0.0 Model
 * Author: Aru
 * Creation Date: 7 nov. 2020 at 13:59:26
 *********************************************/

 int nbVertex = ...;
range Vertex = 1..nbVertex;

float opti = ...; //exact solution optimum
float Z = 1.3 * opti; //optimum majoration

float alpha = 0.99; // alpha >= 0.5 !!!

float c[Vertex, Vertex] = ...; //cost

float V[Vertex, Vertex] = ...; //covariance matrix (generated)

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
	
	
	//stochastic constraint	(Shore approximation)
	//center and reduce Z : (Z - avg(c)*x) / V^0.5*x = N(0,1)
	
	//         (Z - avg(c)*x)              >=           phi^-1(alpha)               *            V^0.5*x
	(Z - sum(i,j in Vertex) c[i,j]*x[i,j]) >= 5.5556 * (1-((1-alpha)/alpha)^0.1185) * (sum(i,j in Vertex) (V[i,j]^0.5*x[i,j]));
	
	
}