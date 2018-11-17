
/*----------------------------------------------------------------------------------------------------
	
	Allele class member function definitions

	Description: represents a concrete version of a gene trait, e.g. "blue eyes"

----------------------------------------------------------------------------------------------------*/


#include "allele.h"
#include <cassert>

using namespace std;



/*----------------------------------------------------------------------------------------------------
	Default constructor
----------------------------------------------------------------------------------------------------*/

Allele::Allele(){
	nucleotideSequence = "";		// e.g. AGTC
	type = "";						// e.g. Recessive
	variation = "";					// e.g. Blue eyes
}

/*----------------------------------------------------------------------------------------------------
	Parametized constructor
----------------------------------------------------------------------------------------------------*/

Allele::Allele(const string& v, const string& t, const string& sequence){
	this->variation = v;	
	this->type = t;
	this->nucleotideSequence = sequence;
}

/*----------------------------------------------------------------------------------------------------
	SetExpressionType( string theExpressionType )
	
	Description: 	Setter method for expression type. Allows a user to enter variants of string
					dominant and recessive, selects the intended type and sets member variable
----------------------------------------------------------------------------------------------------*/

void Allele::SetExpressionType(string t){

	const string DOMINANT_STRING = "dom";
	const string RECESSIVE_STRING = "rec";

	// make everything lowercase
    transform(t.begin(), t.end(), t.begin(), ::tolower); 
	
	// user entered or meant to enter "dominant"
	if (t.find(DOMINANT_STRING) != std::string::npos){
		this->type = expression_string[RECESSIVE];
	}
	// user entered or meant to enter "recessive"
	else if(t.find(RECESSIVE_STRING) != std::string::npos){
		this->type = expression_string[DOMINANT];
	}
	// user entered something that wasn't dominant or recessive
	else{
		this->type = expression_string[NONE];
	}
}

/*----------------------------------------------------------------------------------------------------
	WriteAlleleToFile( outputfilestream object )
	
	Description: 	Writes the state data of this object to the filestream input parameter 
----------------------------------------------------------------------------------------------------*/

void	Allele::WriteAlleleToFile(ofstream& of){

	of	  << this->variation
	  << ","
	  << this->type
	  << ","	   	  
	  << this->nucleotideSequence;
}

/*----------------------------------------------------------------------------------------------------
	operator==(  )
	
	Description: 	returns true if the state data of this object is equivallent to comparison object
----------------------------------------------------------------------------------------------------*/

bool Allele::operator==(const Allele& rhs){

	bool isEqual = false;

	if( 
		this->nucleotideSequence == rhs.nucleotideSequence &&
		this->type == rhs.type &&
		this->variation == rhs.variation
	){
		isEqual = true;
	}
	return isEqual;
}

/*----------------------------------------------------------------------------------------------------
	operator!=(  )
	
	Description: 	returns true if the state data of this object is NOT equivallent to comparison object
----------------------------------------------------------------------------------------------------*/

bool Allele::operator!=(const Allele& rhs){
	   return !(*this == rhs);
}


/*----------------------------------------------------------------------------------------------------
	RunUnitTest()
	
	Description: 	returns true if 'unit test' for this object pass
----------------------------------------------------------------------------------------------------*/

 bool Allele::RunUnitTests(){

	 // TODO: @schroeder - add unit tests to Allele class
	 bool testStatus = false;

	// test default constuctor
	Allele testAllele;
	assert(testAllele.GetNucleotide() == "");
	assert(testAllele.GetVariation() == "");
	assert(testAllele.GetExpressionType() == "");

	// test parametized constructor
	Allele testAllele2("variationTest", "typeTest", "sequenceTest");
	assert(testAllele2.GetNucleotide() == "sequenceTest");
	assert(testAllele2.GetVariation() == "variationTest");
	assert(testAllele2.GetExpressionType() == "typeTest");

	// test overloaded operator
	Allele testAllele3("variationTest", "typeTest", "sequenceTest");
	Allele testAllele4("variationTest", "typeTest", "sequenceTest");			
	if( testAllele3 == testAllele4 ){
		testStatus = true;
	}

	return testStatus;
}