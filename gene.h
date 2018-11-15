#ifndef GENE_H 
#define GENE_H

#include <iostream>
#include <string>
#include <fstream>
#include "allele.h"


using namespace std;


/*----------------------------------------------------------------------------------------------------
	Gene class definition
----------------------------------------------------------------------------------------------------*/
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
		void	SetTrait(string trait) {traitType = trait;}
		void	SetName(string n){name = n;}

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


Gene::Gene(){}

Gene::Gene(Allele a, Allele b){

	this->a = a;
	this->b = b;
}


Allele Gene::GetExpressedTrait(){

	Allele expressedAllele;

	if(this->a.GetExpressionType() == expression_string[DOMINANT]){
		expressedAllele = this->a;
	}
	else{
		expressedAllele = this->b;
	}
	return expressedAllele;
}

void Gene::WriteGeneToFile(ofstream& of){

	// write out in format; UH56,Hair Color,Blonde,TTCC,Black,CAGG
  	of << this->name << "," << this->traitType << ",";
	
	this->a.WriteAlleleToFile(of);
	
	this->b.WriteAlleleToFile(of);
	 	   	  
	of  << this->b.GetNucleotide() << "\n";
}

bool Gene::operator==(const Gene& rhs){

	bool isEqual = false;

	if( 
		this->GetName() == rhs.GetName() && 
		this->GetTrait() == rhs.GetTrait() &&
		this->a == rhs.a &&
		this->b == rhs.b 
		){
			isEqual = true;
	}
	return isEqual;
}

bool Gene::operator!=(const Gene& rhs){
	return !(*this == rhs);
}

bool Gene::RunUnitTests(){

	bool testStatus = true;
	return testStatus;
}

#endif