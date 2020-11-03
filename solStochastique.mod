/*********************************************
 * OPL 12.9.0.0 Model
 * Author: Aru
 * Creation Date: 3 nov. 2020 at 10:50:26
 *********************************************/

 
int nbVertex = ...;

range Vertex = 1..nbVertex;

float opti = ...; //exact solution optimum

float Z = 0.3 * opti; //optimum majoration

float c[Vertex, Vertex] = ...; //average cost

//TODO : probability version
//importer la table de la loi normale (en dat)

tuple Subtour
{
	int size;
	{int} subtour;
}
{Subtour} Subtours = ...; //generated in another file

float alpha = 0.9;


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
		sum(i,j in S.subtour) x[i,j] <= S.size - 1;
	}
	
	//stochastic constraint

	//Utiliser la fonction de répartition (comment faire pour calculer les integrales ?)
	//Probabilité : différente pour chaque x(ij)
	
	//Matrice variance covariance -> comment elle est generee ?
	//covariance entre deux points vs. covariance d'un arc (??)
	
	//Ce sont bien les couts qui sont aleatoires
	
	//sum(i,j in Vertex) 
	
	//-> somme des moyenne + somme des variances  => N(sum(avg), sum(var))


}