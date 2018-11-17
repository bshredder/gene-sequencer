

/*----------------------------------------------------------------------------------------------------
	Gene class member function definitions

	Description:	represents a location on a chromosome that provides a pair of alleles. Contains
					behaivor that selects how and when an ellele is expressed as genotype
----------------------------------------------------------------------------------------------------*/


#include "gene.h"

using namespace std;


/*----------------------------------------------------------------------------------------------------
	Default constructor
----------------------------------------------------------------------------------------------------*/

Gene::Gene(){}

/*----------------------------------------------------------------------------------------------------
	Paramatized constructor
----------------------------------------------------------------------------------------------------*/

Gene::Gene(Allele a, Allele b){

	this->a = a;
	this->b = b;
}

/*----------------------------------------------------------------------------------------------------
	GetExpressedTrait

	Description - 	encodes the logic for which allele is expressed. Naive implementation is to 
					return the dominant allele
----------------------------------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------------------------------
	WriteGeneToFile(outputfilestream object)

	Desription: writes gene state data to filestream object
----------------------------------------------------------------------------------------------------*/

void Gene::WriteGeneToFile(ofstream& of){

	// write out in format; UH56,Hair Color,Blonde,TTCC,Black,CAGG
  	of << this->name << "," << this->traitType << ",";
	
	this->a.WriteAlleleToFile(of);
	
	this->b.WriteAlleleToFile(of);
	 	   	  
	of  << this->b.GetNucleotide() << "\n";
}

/*----------------------------------------------------------------------------------------------------
	operator==
----------------------------------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------------------------------
	operator!=
----------------------------------------------------------------------------------------------------*/

bool Gene::operator!=(const Gene& rhs){
	return !(*this == rhs);
}

/*----------------------------------------------------------------------------------------------------
	RunUnitTest()
----------------------------------------------------------------------------------------------------*/

bool Gene::RunUnitTests(){

	// TODO @schroeder - implment Gene Unit Tests
	bool testStatus = false;

	// does gene return the correct expressed trait
	Gene testGene( Allele("blue", "rec", "GAGA"), Allele("brown","dom","TATA"));
	Allele testAllele = testGene.GetExpressedTrait();
	if(testAllele.GetVariation() == "brown"){
		testStatus = true;	
	}

	return testStatus;
}
