/*********************************************
 * OPL 12.9.0.0 Model
 * Author: Aru
 * Creation Date: 8 nov. 2020 at 10:31:56
 *********************************************/
 
{float} alpha = ...;
{float} stdCoef = ...;
 
int timeLimit = ... ;


main {
	
	thisOplModel.generate();
	var Data = thisOplModel.dataElements;
	
	var fResult = new IloOplOutputFile();
	fResult.open("resultsSimu.csv");
	
	var optimumMTZ;
	
	var data = "d6";
	
//Partie Deterministe -------------------------------------  
		
	function computeSolDeterministeMTZ()
	{
		var subSource = new IloOplModelSource("solDeterministeMTZ.mod");
		var subDef = new IloOplModelDefinition(subSource);
		var subCplex = new IloCplex();
		var subDataSource = new IloOplDataSource("data/"+ data +".dat");
		
		subCplex.tilim = Data.timeLimit;
		
		var Opl0 = new IloOplModel(subDef, subCplex);
		
		Opl0.addDataSource(subDataSource);
		Opl0.generate();
		
		if (subCplex.solve()) 
		{	
			optimumMTZ = subCplex.getBestObjValue();
			Opl0.postProcess();	
		}								
		else 
		{
			writeln("ERROR IN DETERMINISTIC COMPUTATION !!");
		}
		
		subDataSource.end();
		subSource.end();
		subCplex.end();
		subDef.end();     
	}
	
	
//Partie Stochastique -------------------------------------

	function computeSolStochastique()
	{
		var subSource = new IloOplModelSource("solStochastique.mod");
		var subDef = new IloOplModelDefinition(subSource);
		var subCplex = new IloCplex();
		var subDataSource = new IloOplDataSource("data/"+ data +".dat");
		var subDataSource2 = new IloOplDataSource("data/"+ data +"_subtours.dat");
		
		var varData = new IloOplDataElements();
		varData.opti = optimumMTZ; //add the optimum value to the model's variables
		varData.alpha = a;
		varData.stdDevCoef = std;
		
		subCplex.tilim = Data.timeLimit;
		
		var Opl0 = new IloOplModel(subDef, subCplex);
		
		Opl0.addDataSource(subDataSource);
		Opl0.addDataSource(subDataSource2);
		Opl0.addDataSource(varData);
		Opl0.generate();
		
		var debut = new Date();
		var temp = debut.getTime();
		
		if (subCplex.solve())
		{	
			var fin = new Date();
			
			fResult.write(subCplex.getBestObjValue(), ";");
			fResult.write(subCplex.getObjValue(), ";");
			
			fResult.write(fin.getTime() - temp);
			Opl0.postProcess();
       }
       else 
       {
			writeln("ERROR IN STOCHASTIC COMPUTATION !!");
       }
		
		subDataSource.end();
		subSource.end();
		subCplex.end();
		subDef.end();
	}
	
	function computeSolStochastiqueMTZ()
	{
		var subSource = new IloOplModelSource("solStochastiqueMTZ.mod");
		var subDef = new IloOplModelDefinition(subSource);
		var subCplex = new IloCplex();
		var subDataSource = new IloOplDataSource("data/"+ data +".dat");
		
		var varData = new IloOplDataElements();
		varData.opti = optimumMTZ; //add the optimum value to the model's variables
		varData.alpha = a;
		varData.stdDevCoef = std;
		
		subCplex.tilim = Data.timeLimit;
		
		var Opl0 = new IloOplModel(subDef, subCplex);
		
		Opl0.addDataSource(subDataSource);
		Opl0.addDataSource(varData);
		Opl0.generate();
		
		var debut = new Date();
		var temp = debut.getTime();
		
		if (subCplex.solve())
		{	
			var fin = new Date();
			
			fResult.write(subCplex.getBestObjValue(), ";");
			fResult.write(subCplex.getObjValue(), ";");
			
			fResult.write(fin.getTime() - temp);
			Opl0.postProcess();
       }
       else 
       {
			writeln("ERROR IN STOCHASTIC COMPUTATION !!");
       }
		
		subDataSource.end();
		subSource.end();
		subCplex.end();
		subDef.end();     
	}
	
	
//Processing et ecriture des resultats
	fResult.write("param;best;obj;timeStocha;best;obj;timeStochaMTZ;"); //en-tete du csv
	fResult.writeln();
	
	computeSolDeterministeMTZ(); //get the optimum
	
	for (var a in Data.alpha)
	{
		for (var std in Data.stdCoef)
		{	
		    fResult.write("(", a, ", ", std, ")", ";");
		    
			computeSolStochastique(a, std);
		    fResult.write(";");
		    computeSolStochastiqueMTZ(a, std);
		    
		    fResult.writeln();    
  		}    
    }
    
    fResult.close();
    
}  