#pragma once

#include <cassert>
#include "chromosome.h"

using namespace std;
	

enum choice_type { CREATE = 1, ANALYZE, INPUT, OUTPUT, EXIT};

class GeneSequencer{

	public:

		// runs the gene sequencer - displays menu and calls appropriate method from user choice
		void Run();

        // executes all unit tests on each object. Returns true if all tests pass
        bool PowerOnSelfTest();	

	private:

		ChromosomePair c;

		// default constructor
		ChromosomePair 	CreateChromosomePair();

		// displays and gets the users menu choice
		int DisplayUserMenu();

		// displays the dominant allele of each gene in chromosome
		void AnalyzeChromosomePair();		

		// returns a chromosome object from data in 'filename'
		ChromosomePair 	ImportChromosomePair(const string& fileName = "");

		// saves chromosome 'c' data to file 'filename' 
		void ExportChromosomePair(ChromosomePair c, const string& fileName = "");

		// returns chromosome from 'x' and 'y' genes - allele selection is random
		ChromosomePair 	DoMeiosis(ChromosomePair x, ChromosomePair y);

		// outputs genotype (dominant alleles for each gene) in 'c'
		void SequenceChromosomePair(ChromosomePair c);

	private:

};