
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
Gene ChromosomePair::FindGene(string name){
	
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
	
	Description: given two chromosomes produces a chromosome pair with dominant alleles
----------------------------------------------------------------------------------------------------*/
ChromosomePair ChromosomePair::operator+(ChromosomePair rhs){

	ChromosomePair newPair;
	int randomSelection = 0;

	Allele 	newAlleleA, newAlleleB;

	// pick one of two alleles randomly from each gene in this chromosome
	// pick one of two alleles randomly from each matchin gene in rhs
	for (Gene g : this->genes){

		// coin flip to see which allele gets passed on from this gene
		randomSelection = rand()%2; 
		if( 0 == randomSelection){
			// pass on allele a
			newAlleleA = g.GetAlleleA();
		}
		else if(1 == randomSelection){
			// pass on allele b
			newAlleleA = g.GetAlleleB();
		}
		else{
			cout << "ERROR in Chromosome operator" << endl;
		}

		// coin flip to see which allele gets passed on from rhs gene
		randomSelection = rand()%2; 
		if( 0 == randomSelection){
			// pass on allele a
			newAlleleB = rhs.FindGene(g.GetName()).GetAlleleA();
		}
		else if(1 == randomSelection){
			// pass on allele b
			newAlleleB = rhs.FindGene(g.GetName()).GetAlleleB();
		}
		else{
			cout << "ERROR in Chromosome operator" << endl;
		}		
	
		Gene newGene(newAlleleA, newAlleleB);
		newGene.SetName(g.GetName());
		newGene.SetTrait(g.GetTrait());
		newPair.AddGene(newGene);
	} 

	return newPair;
}


 
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

bool ChromosomePair::RunUnitTests(){

	bool testStatus = true;
	return testStatus;
}



