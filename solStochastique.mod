/*********************************************
 * OPL 12.9.0.0 Model
 * Author: Aru
 * Creation Date: 3 nov. 2020 at 10:50:26
 *********************************************/
 
 
int nbVertex = ...;
range Vertex = 1..nbVertex;

float opti = ...; //exact solution optimum
float Z = 1.3 * opti; //optimum majoration

float alpha = 0.99; // alpha >= 0.5 !!!

float c[Vertex, Vertex] = ...; //average cost

float V[Vertex, Vertex] = ...; //covariance matrix (generated)

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
	forall (i in Vertex)
	{
		x[i,i] == 0;	 //ignores loops
	}
	
	forall(i,j in Vertex)
	{
		x[i,j] == 0 || x[i,j] == 1;   // x(i,j) c {0,1}
	}
	
	forall(i in Vertex) sum(j in Vertex) x[i,j] == 1;   //only one input and output path per vertex
	forall(j in Vertex) sum(i in Vertex) x[i,j] == 1;
	
	forall(S in Subtours)   //subtour
	{
		sum(i,j in S.subtour) x[i,j] <= S.len - 1;
	}
	
	//stochastic constraint	(Shore approximation)
	//center and reduce Z : (Z - avg(c)*x) / V^0.5*x = N(0,1)
	
	//         (Z - avg(c)*x)              >=           phi^-1(alpha)               *            V^0.5*x
	(Z - sum(i,j in Vertex) c[i,j]*x[i,j]) >= 5.5556 * (1-((1-alpha)/alpha)^0.1185) * (sum(i,j in Vertex) (V[i,j]^0.5*x[i,j]));
	
	
	//stochastic constraint	
	//if value 0.63 => takes the result in table[6,3]
	//table[ftoi(  trunc( (Z - sum(i,j in Vertex) c[i,j]*x[i,j]) / sum(i,j in Vertex) (sqrt(V[i,j])*x[i,j])* 10 )  ), 
	//      ftoi(  trunc( (Z - sum(i,j in Vertex) c[i,j]*x[i,j]) / sum(i,j in Vertex) (sqrt(V[i,j])*x[i,j])* 100)  ) mod 10] //ex: 63 mod 10 = 3
	//     >= alpha;

}