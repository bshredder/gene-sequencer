/*----------------------------------------------------------------------------------------------------
	Chromosome Class Definition

	Description: 	A collection of genes that make up a subset of an organisms traits
----------------------------------------------------------------------------------------------------*/

#ifndef CHROMOSOME_H 
#define CHROMOSOME_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <ios>
#include <time.h>
#include <stdlib.h>
#include "gene.h"
#include "punnetteSquare.h"


using namespace std;


class ChromosomePair{

	public: 

		// default constructor
		ChromosomePair();

		// outputs genotype which is each dominant allele in each gene
		void AnalyzeGenotype();		

		// configures this chromosome with data from filestream 'ifs'
		void 	InputFromFile(ifstream& ifs);

		// writes the state data from this chromosome to filestream 'ofs'
		void	OutputToFile(ofstream& ofs);

		// adds a new Gene object 'g' to a collection in this object
		void 	AddGene(Gene g);

		// returns a Gene object that matches a Gene with name 'n'
		Gene	FindGene(const string& n);

		// returns a Gene object that matches a gene index i
		Gene	FindGene(const int i) {return this->genes.at(i);}
		
		// returns a chromosome that is a recombination of one Allele from each of two genes - random selection 
		ChromosomePair operator+(ChromosomePair rhs);

		// overloadded opererators
		bool operator==(const ChromosomePair& rhs);
		bool operator!=(const ChromosomePair& rhs);

		bool RunUnitTests();

	private:

		vector<Gene> 	genes;
		string 			fileName;
		PunnetteSquare	ps;
};


#endif