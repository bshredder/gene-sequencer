
/*----------------------------------------------------------------------------------------------------
	Gene class definition

	Description:	represents a location on a chromosome that provides a pair of alleles. Contains
					behaivor that selects how and when an ellele is expressed as genotype
----------------------------------------------------------------------------------------------------*/

#ifndef GENE_H 
#define GENE_H

#include <iostream>
#include <string>
#include <fstream>
#include "allele.h"

using namespace std;


class Gene {

	public:

		// default constructor  
		Gene();

		// parametized constructor - a gene has two alleles
		Gene(Allele a, Allele b);

		// creates a gene from data in filestream
		void 	ReadGeneFromFile(ifstream& ifs);

		// writes state data of this gene to filestream
		void 	WriteGeneToFile(ofstream& ofs);

		// returns the dominant allele of this gene - genotype
		Allele 	GetExpressedTrait();

		// accessor (getter) methods
		string	GetTrait() const {return traitType;}
		string 	GetName() const {return name;}
		Allele	GetAlleleA(){return this->a;}
		Allele 	GetAlleleB(){return this->b;}		

		// mutator (setter) methods
		void	SetTrait(const string& trait) {traitType = trait;}
		void	SetName(const string& n){name = n;}

		// equality operator
		bool operator==(const Gene& rhs);
		bool operator!=(const Gene& rhs);

		bool	RunUnitTests();

	private:

		// determine the genotype - which allele is dominant
		expression_type CalculateExpression();

		string  	name;
		string		traitType;
		Allele 		a;
		Allele		b;

};


#endif