
/*----------------------------------------------------------------------------------------------------
	ChromosomePair class member function definitions 
----------------------------------------------------------------------------------------------------*/

#include "chromosome.h"

using namespace std;


/*----------------------------------------------------------------------------------------------------
	ChromosomePair() 
	
	Description: default constructor
----------------------------------------------------------------------------------------------------*/

ChromosomePair::ChromosomePair(){

	// seed the random number generator to simulate meiosis
	srand (time(NULL));
}


/*----------------------------------------------------------------------------------------------------
	FineGene(string name) 
	
	Description: given a gene name - finds it in the collection of genes if it exists
----------------------------------------------------------------------------------------------------*/

Gene ChromosomePair::FindGene(const string& name){
	
	Gene match;

	for (Gene g : this->genes){
		if( g.GetName() == name){
			match = g;
		}
	}	
	return match;
}


/*----------------------------------------------------------------------------------------------------
	Overloaded operator+ 
	
	Description: 	Given two chromosomes simulates meiosis by creating a new chromosome that inherits
					according to the probablities of a punnette square the alleles from both parent
					chromosomes
----------------------------------------------------------------------------------------------------*/

ChromosomePair ChromosomePair::operator+(ChromosomePair rhs){

	const int 		TWO_DOMINANT = 0;
	const int 		TWO_RECESSIVE = 1;
	const int 		DOMINANT_AND_RECESSIVE = 2;
	const int 		MAX_ALLELE_COMBINATIONS = 4;	

	ChromosomePair 	newPair;
	Allele 			newAlleleA, newAlleleB;	
	int 			randomSelection = 0;

	for (Gene g : this->genes){

		// create a punnette square for the two genes of the two chomosomes	
		PunnetteSquare pSquare(g, rhs.FindGene(g.GetName()));

		// given the two chromosomes calculate probabilities of meiosis outcome with a Punnette Square
		double probDD = pSquare.CalculateDominantProbablity();
		double probrr = pSquare.CalculateRecessiveProbablity();
		double probDr = pSquare.CalculateDominantRecessiveProbablity();

		// create a 'allele drawer' with the Punnette Square proportions
		int probabiltyMask[MAX_ALLELE_COMBINATIONS];

		// calculate how many of each type of allele to put in the 'drawer' 
		int numDom 		= probDD * MAX_ALLELE_COMBINATIONS;
		int numRec 		= probrr * MAX_ALLELE_COMBINATIONS;
		int numDomRec 	= probDr * MAX_ALLELE_COMBINATIONS;
		
		// put the alleles in the 'drawer'
		int index = 0;
		for(index = 0; index < numDom; index++){probabiltyMask[index] = TWO_DOMINANT;}
		for(;index < numRec; index++){probabiltyMask[index] = TWO_RECESSIVE;}
		for(;index < numDomRec; index++){probabiltyMask[index] = DOMINANT_AND_RECESSIVE;}		

		// randomly pick an allele from the probablitically determined 'drawer' of alleles  		
		randomSelection = rand() % MAX_ALLELE_COMBINATIONS;

		if(probabiltyMask[randomSelection] == TWO_DOMINANT  ){
			// pass on two dominant alleles
			newAlleleA = pSquare.GetDominantAllele();
			newAlleleB = pSquare.GetDominantAllele();
		}
		else if(probabiltyMask[randomSelection] == TWO_RECESSIVE ){
			// pass on two recessive alleles
			newAlleleA = pSquare.GetRecessiveAllele();
			newAlleleB = pSquare.GetRecessiveAllele();
		}
		else if(probabiltyMask[randomSelection] == DOMINANT_AND_RECESSIVE){
			// pass on dom & rec alleles
			newAlleleA = pSquare.GetDominantAllele();
			newAlleleB = pSquare.GetRecessiveAllele();
		}
		else{
			cout << "ERROR: Chromosome meiosis" << endl;
		}
		
		Gene newGene(newAlleleA, newAlleleB);
		newGene.SetName(g.GetName());
		newGene.SetTrait(g.GetTrait());
		newPair.AddGene(newGene);
	} 
	return newPair;
}


 /*----------------------------------------------------------------------------------------------------
	Overloaded operator==
----------------------------------------------------------------------------------------------------*/

bool ChromosomePair::operator==(const ChromosomePair& rhs){

	bool isEqual = false;

	if( this->genes.size() == 0 && rhs.genes.size() == 0){
		isEqual = true;
	}

	else{
		for (Gene g : this->genes){ 	
			for(Gene gg : rhs.genes){
				if( g == gg){
					isEqual = true;
				}
			}
		}
	}
	return isEqual;
}


 /*----------------------------------------------------------------------------------------------------
	Overloaded operator!=
----------------------------------------------------------------------------------------------------*/

bool ChromosomePair::operator!=(const ChromosomePair& rhs){
	return !(*this == rhs);
}

/*----------------------------------------------------------------------------------------------------
	InputFromFile() 
	
	Description: given a valid filename, create a collection of gene objects 
----------------------------------------------------------------------------------------------------*/

void ChromosomePair::InputFromFile(ifstream& file){

	//ifstream file( f );
	string geneData, name, trait, variationA, typeA, sequenceA, variationB, typeB, sequenceB;

	while ( file.good() ){

		// get the whole line, e.g.: UH56,Hair Color,Blonde,TTCC,Black,CAGG
     	getline( file, geneData ); 

		// now parse the line
		istringstream isA(geneData);
	
		getline(isA, name, ',');
		getline(isA, trait, ',');
		getline(isA, variationA, ',');
		getline(isA, typeA, ',');				
		getline(isA, sequenceA, ',');
		Allele alleleA(variationA, typeA, sequenceA);

		getline(isA, variationB, ',');
		getline(isA, typeB, ',');				
		getline(isA, sequenceB, ',');
		Allele alleleB(variationB, typeB, sequenceB);	

		Gene newGene(alleleA, alleleB);
		newGene.SetName(name);	
		newGene.SetTrait(trait);

		 genes.push_back(newGene); 
	}
}

/*----------------------------------------------------------------------------------------------------
	OutputToFile() 
	
	Description: create a file called filename and stream collection of gene objects  to file 
----------------------------------------------------------------------------------------------------*/

void ChromosomePair::OutputToFile(ofstream& myfile){
  	
	// ofstream myfile;
  	// myfile.open (fileName, std::ios_base::app);

	for( unsigned int i = 0; i < genes.size(); i++){
		genes.at(i).WriteGeneToFile(myfile);
	}
  	//myfile.close();
}

/*----------------------------------------------------------------------------------------------------
	AddGene() 
	
	Description: add a gene to chromosome 
----------------------------------------------------------------------------------------------------*/

void ChromosomePair::AddGene(Gene g){
	this->genes.push_back(g);
}

/*----------------------------------------------------------------------------------------------------
	AnalyzeGenotype()
	
	Description: output to screen the contents of each gene in chromosome collection
----------------------------------------------------------------------------------------------------*/

void ChromosomePair::AnalyzeGenotype(){

	cout << flush;
	cout << setw(15) << "CHROMOSOME MAP" << endl << endl; 

	for(unsigned int i = 0; i < genes.size(); i++){
		string concat = "Gene " + std::to_string(i);
		cout << setw(25) << left << concat << endl;
		cout << setw(25) << left << "Name: ";
		cout << setw(20) << right << genes.at(i).GetName() << endl;
		cout << setw(25) << left << "Genetic trait: ";
		cout << setw(20) << right << genes.at(i).GetTrait() << endl;
		cout << setw(25) << left << "Expressed allele: ";
		concat = genes.at(i).GetExpressedTrait().GetVariation() + " is " + genes.at(i).GetExpressedTrait().GetExpressionType();
		cout << setw(20) << right << concat << endl;
		cout << setw(25) << left << "Nucleotide sequence: ";
		cout << setw(20) << right << genes.at(i).GetExpressedTrait().GetNucleotide() << endl << endl;		
	}
}

/*----------------------------------------------------------------------------------------------------
	RunUnitTests()
	
	Description: 
----------------------------------------------------------------------------------------------------*/

bool ChromosomePair::RunUnitTests(){

	// TODO @schroeder implement generic streams file and string streams
	bool testStatus = true;

	/*
		test data
		rR - UH56,hair color,blonde,recessive,TTCC,Black,dominant,CAGG
		rr - MADEUP1,earlobes,connected,recessive,TCGC,connected,recessive,TCGC
		RR - MADEUP2,earlobes,unconnected,dominant,TC,unconnected,dominant,TC
	*/

	// create test data; alleles, genes, punnette squares
	Allele allele_r("blonde", "recessive", "TTCC");
	Allele allele_R("Black", "dominant", "CAGG");
	Gene rr(allele_r, allele_r);
	Gene rR(allele_r, allele_R);
	Gene RR(allele_R, allele_R);
	PunnetteSquare ps_rr_rr(rr, rr);
	PunnetteSquare ps_rR_rR(rR, rR);
	PunnetteSquare ps_RR_RR(RR, RR);
	PunnetteSquare ps_RR_rr(RR, rr);
	PunnetteSquare ps_rR_rr(rR, rr);

	// test punnette squares
	cout << "double recessive: should be 100% recessive " << endl;
	cout << "Calculate recessive: " << ps_rr_rr.CalculateRecessiveProbablity() << endl;
	cout << "Calculate dominant: " << ps_rr_rr.CalculateDominantProbablity() << endl;
	cout << "Calculate dominant/recessive: " << ps_rr_rr.CalculateDominantRecessiveProbablity() << endl;
	ps_rr_rr.PrintSquare();
	
	cout << "double dominant: should be 100% dominant " << endl;
	cout << "Calculate recessive: " << ps_RR_RR.CalculateRecessiveProbablity() << endl;
	cout << "Calculate dominant: " << ps_RR_RR.CalculateDominantProbablity() << endl;
	cout << "Calculate dominant/recessive: " << ps_RR_RR.CalculateDominantRecessiveProbablity() << endl;
	ps_RR_RR.PrintSquare();	

	cout << "recessive/dominant + recessive/dominant: should be 50% d/r " << endl;
	cout << "Calculate recessive: " << ps_rR_rR.CalculateRecessiveProbablity() << endl;
	cout << "Calculate dominant: " << ps_rR_rR.CalculateDominantProbablity() << endl;
	cout << "Calculate dominant/recessive: " << ps_rR_rR.CalculateDominantRecessiveProbablity() << endl;
	ps_rR_rR.PrintSquare();


	// test adding chromosomes
	ChromosomePair c1, c2, c3;
	c1.AddGene(rr);
	c2.AddGene(rr);
	c3 = c1 + c2;

	ChromosomePair c4, c5, c6;
	c4.AddGene(RR);
	c5.AddGene(RR);
	c6 = c4 + c5;

	ChromosomePair c7, c8, c9;
	c7.AddGene(rR);
	c8.AddGene(rR);
	c9 = c7 + c8;

	return testStatus;
}



