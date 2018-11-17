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
