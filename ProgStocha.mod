/*********************************************
 * OPL 12.9.0.0 Model
 * Authors: G. GOSSET, Q. LASOTA, T. PICHARD, G. SCION
 * Creation Date: 31 oct. 2020 at 14:18:18
 *********************************************/
 
int nbVertex = ...;
 
range Vertex = 1..nbVertex;

int c[Vertex, Vertex] = ...;


dvar boolean x[Vertex,Vertex];


minimize sum(v1,v2 in Vertex) x[v1, v2] * c[v1,v2];

subject to{

	forall (v in Vertex){
		x[v,v] == 0;	 //ignores loops
	}
	
	forall(v1,v2 in Vertex){	
		x[v1, v2] == 0 || x[v1, v2] == 1;   // x(i,j) c {0,1}
	}

	forall(i in Vertex) { sum(j in Vertex) x[i,j] == 1;} //only one input and output path per vertex
	forall(j in Vertex) { sum(i in Vertex) x[i,j] == 1;}
	
	//forall(S in )    //subtour

}