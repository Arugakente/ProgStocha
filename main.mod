/*********************************************
 * OPL 12.9.0.0 Model
 * Author: G. GOSSET, Q. LASOTA, T. PICHARD, G. SCION
 * Creation Date: 3 nov. 2020 at 10:19:05
 *********************************************/
 
{string} datafile = ...;
{string} datafileMTZ = ...;
int timeLimit = ... ;

main {
	
	thisOplModel.generate();
	var Data = thisOplModel.dataElements;
	
	var fResult = new IloOplOutputFile();
	fResult.open("resultsMain.csv");
	
	var optimum;
	var optimumMTZ;
	
	var alpha = 0.30;
	var standardDeviationCoef = 0.10;
	
//Partie Deterministe -------------------------------------  

	function computeSolDeterministe()
	{
		var subSource = new IloOplModelSource("solDeterministe.mod");
		var subDef = new IloOplModelDefinition(subSource);
		var subCplex = new IloCplex();
		var subDataSource = new IloOplDataSource("data/"+ s +".dat");
		var subDataSource2 = new IloOplDataSource("data/"+ s +"_subtours.dat");
		
		subCplex.tilim = Data.timeLimit;
		
		var Opl0 = new IloOplModel(subDef, subCplex);
		
		Opl0.addDataSource(subDataSource);
		Opl0.addDataSource(subDataSource2);
		Opl0.generate();
		
		var debut = new Date();
		var temp = debut.getTime();
		
		if (subCplex.solve()) 
		{	
			var fin = new Date();
			
			fResult.write(subCplex.getBestObjValue(), ";");
			fResult.write(subCplex.getObjValue(), ";");
			
			optimum = subCplex.getBestObjValue();
			
			fResult.write(fin.getTime() - temp);
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
	
	
	function computeSolDeterministeMTZ()
	{
		var subSource = new IloOplModelSource("solDeterministeMTZ.mod");
		var subDef = new IloOplModelDefinition(subSource);
		var subCplex = new IloCplex();
		var subDataSource = new IloOplDataSource("data/"+ s +".dat");
		
		subCplex.tilim = Data.timeLimit;
		
		var Opl0 = new IloOplModel(subDef, subCplex);
		
		Opl0.addDataSource(subDataSource);
		Opl0.generate();
		
		var debut = new Date();
		var temp = debut.getTime();
		
		if (subCplex.solve()) 
		{	
			var fin = new Date();
			
			fResult.write(subCplex.getBestObjValue(), ";");
			fResult.write(subCplex.getObjValue(), ";");
			
			optimumMTZ = subCplex.getBestObjValue();
			
			fResult.write(fin.getTime() - temp);
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
		var subDataSource = new IloOplDataSource("data/"+ s +".dat");
		var subDataSource2 = new IloOplDataSource("data/"+ s +"_subtours.dat");
		
		var varData = new IloOplDataElements();
		varData.opti = optimum; //add the optimum value to the model's variables
		varData.alpha = alpha;
		varData.stdDevCoef = standardDeviationCoef;
		
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
		var subDataSource = new IloOplDataSource("data/"+ s +".dat");
		
		var varData = new IloOplDataElements();
		varData.opti = optimumMTZ; //add the optimum value to the model's variables
		varData.alpha = alpha;
		varData.stdDevCoef = standardDeviationCoef;
		
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
	fResult.write("dataName;bestObjDeter;objDeter;processTimeDeter;bestObjStocha;objStocha;processTimeStocha;"); //en-tete du csv
	fResult.writeln();
	
	for (var s in Data.datafile)
	{
    fResult.write(s, ";");
    computeSolDeterministe(s);
    fResult.write(";");
    computeSolStochastique(s);
    fResult.writeln();
    }
    
    for (var s in Data.datafileMTZ)
	{
    fResult.write(s + "_MTZ", ";");
    computeSolDeterministeMTZ(s);
    fResult.write(";");
    computeSolStochastiqueMTZ(s);
    fResult.writeln();
    }
    
    fResult.close();
    
}  