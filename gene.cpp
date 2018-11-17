
#include "gene.h"

using namespace std;



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
