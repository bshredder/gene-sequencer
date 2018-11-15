#pragma once

#include <cassert>
#include "chromosome.h"

using namespace std;

class GeneSequencer{

	public:

		// default constructor
		ChromosomePair 	CreateChromosomePair();

		// returns a chromosome object from data in 'filename'
		ChromosomePair 	ImportChromosomePair(const string& fileName = "");

		// saves chromosome 'c' data to file 'filename' 
		void ExportChromosomePair(ChromosomePair c, const string& fileName = "");

		// returns chromosome from 'x' and 'y' genes - allele selection is random
		ChromosomePair 	DoMeiosis(ChromosomePair x, ChromosomePair y);

		// outputs genotype (dominant alleles for each gene) in 'c'
		void SequenceChromosomePair(ChromosomePair c);

		// executes all unit tests on each object. Returns true if all tests pass
		bool PowerOnSelfTest();

	private:

		

};


ChromosomePair 	GeneSequencer::CreateChromosomePair(){
	
	char moreGenes = 'n';					
	ChromosomePair newChromosome;
	do {

		string name;
		string trait;
		string type;
		string sequence;
		string variant;


		cout << "What is the gene name? (e.g. TZ458)";
		cin >> name;
		cout << "What is the gene trait? (e.g. eye color)";
		cin >> trait;
		cout << "What is allele 1 variant? (e.g. blue/brown/etc.)";
		cin >> variant;
		cout << "What is allele 1 Type? (e.g. dominant/recessive)";
		cin >> type;
		cout << "What is allele 1 nucleotide sequence? (e.g. AGTC)";
		cin >> sequence;
		Allele alleleA(variant, type, sequence);

		cout << "What is allele 2 variant? (e.g. blue/brown/etc.)";
		cin >> variant;
		cout << "What is allele 2 Type? (e.g. dominant/recessive)";
		cin >> type;
		cout << "What is allele 2 nucleotide sequence? (e.g. AGTC)";
		cin >> sequence;
		Allele alleleB(variant, type, sequence);

		Gene newGene(alleleA, alleleB);
		newGene.SetTrait(trait);
		newGene.SetName(name); 
		newChromosome.AddGene(newGene);

		cout << "Would you like to add a new gene? (y/n)" << endl;
		cin >> moreGenes;

		} while (moreGenes == 'y');

		return newChromosome;
}

ChromosomePair 	GeneSequencer::ImportChromosomePair(const string& fileName){
	
	string fn;	
	if( !fileName.empty()){
		fn = fileName;;
	}
	else{
		cin.clear();
		cout << "Enter filename to input chromosome data from: ";
		cin >> fn;
	}

	ChromosomePair c;
	ifstream file( fn );
	c.InputFromFile(file);
	file.close();
	return c;
}

void 	GeneSequencer::ExportChromosomePair(ChromosomePair c, const string& fileName){

	string fn;
	if(!fileName.empty() ){
		fn = fileName;
	}
	else{
		cin.clear();
		cout << "Enter filename to output chromosome data to: ";
		cin >> fn;
	}
	ofstream myfile;
	myfile.open (fn, std::ios_base::app);
	c.OutputToFile(myfile);
	myfile.close();
}
ChromosomePair 	GeneSequencer::DoMeiosis(ChromosomePair x, ChromosomePair y){
	return x + y;
}

void GeneSequencer::SequenceChromosomePair(ChromosomePair c){
	c.AnalyzeGenotype();
}

bool GeneSequencer::PowerOnSelfTest(){

	bool testStatus = true;

	Allele testAllele;
	if(false == testAllele.RunUnitTests() ) {
		cout << "POST ERROR - Allele unit tests" << endl;
		testStatus = false;
	}

	Gene testGene;
	if(false == testGene.RunUnitTests() ){
		cout << "POST ERROR - Gene unit tests" << endl;
		testStatus = false;		
	}

	ChromosomePair testChromosome;
	if(false == testChromosome.RunUnitTests() ){
		cout << "POST ERROR - Chromosome unit tests" << endl;
		testStatus = false;		
	}

	return testStatus;
}