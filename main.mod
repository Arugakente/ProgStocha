/*********************************************
 * OPL 12.9.0.0 Model
 * Author: G. GOSSET, Q. LASOTA, T. PICHARD, G. SCION
 * Creation Date: 3 nov. 2020 at 10:19:05
 *********************************************/
 
{string} datafile = ...;
int timeLimit = ... ;

main {
	
	thisOplModel.generate();
	var Data = thisOplModel.dataElements;
	
	var fResult = new IloOplOutputFile();
	fResult.open("results.csv");
	
	var optimum;
	
//Partie Deterministe	  
	function computeSolDeterministe()
	{
		var subSource = new IloOplModelSource("solDeterministe.mod");
		var subDef = new IloOplModelDefinition(subSource);
		var subCplex = new IloCplex();
		var subDataSource = new IloOplDataSource("data/"+ s +".dat");
		
		subCplex.tilim = Data.timeLimit;
		
		var Opl0 = new IloOplModel(subDef, subCplex);
		
		Opl0.addDataSource(subDataSource);
		Opl0.generate();
		
		var debut = new Date();
		var temp = debut.getTime();
		
		if (subCplex.solve()) {	
		
			var fin = new Date();
			
			fResult.write(subCplex.getBestObjValue(), ";");
			fResult.write(subCplex.getObjValue(), ";");
			
			optimum = subCplex.getBestObjValue();
			
			fResult.write(fin.getTime() - temp);
			Opl0.postProcess();	
		}								
		else {
			writeln("ERROR IN DETERMINISTIC COMPUTATION !!");
		}
		
		subDataSource.end();
		subSource.end();
		subCplex.end();
		subDef.end();     
	}
	
	
//Partie Stochastique
	function computeSolStochastique()
	{
		var subSource = new IloOplModelSource("solStochastique.mod");
		var subDef = new IloOplModelDefinition(subSource);
		var subCplex = new IloCplex();
		var subDataSource = new IloOplDataSource("data/"+ s +".dat");
		var subDataNormalTable = new IloOplDataSource("normalTable.dat");
		
		var optimumData = new IloOplDataElement();
		optimumData.makeElement("opti", optimum); //add the optimum value to the model's variables
		
		subCplex.tilim = Data.timeLimit;
		
		var Opl0 = new IloOplModel(subDef, subCplex);
		
		Opl0.addDataSource(subDataSource);
		Opl0.addDataSource(optimumData);
		Opl0.generate();
		
		var debut = new Date();
		var temp = debut.getTime();
		
		if (subCplex.solve()){	
		
			var fin = new Date();
			
			fResult.write(subCplex.getBestObjValue(), ";");
			fResult.write(subCplex.getObjValue(), ";");
			
			fResult.write(fin.getTime() - temp);
			Opl0.postProcess();
       }
       else {
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
	init(s);
    fResult.write(s, ";");
    computeSolDeterministe(s);
    fResult.write(";");
    computeSolStochastique(s);
    fResult.writeln();
    }
    
    fResult.close();
    
}  