
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;


enum expression_type {RECESSIVE = 0, DOMINANT = 1, NONE = 2};
const static string expression_string[] = {"recessive", "dominant", "none"};

/*----------------------------------------------------------------------------------------------------
	Allele class definition
----------------------------------------------------------------------------------------------------*/

class Allele {

	private:
		string nucleotideSequence;		// e.g. AGTC
		string type;					// e.g. Recessive
		string variation;				// e.g. Blue eyes

	public:

		// default constructor
		Allele();

		// parametized constructor
		Allele(string variation, string type, string sequence);

		// writes state data of this allele to filestream
		void	WriteAlleleToFile(ofstream& of);

		// accessor methods
		string GetNucleotide() const {return nucleotideSequence;}
		string GetExpressionType() const {return type;}
		string GetVariation() const {return variation;}	

		// mutator methods
		void SetNucleotide(string s) {nucleotideSequence = s;}
		void SetExpressionType(string t);
		void SetVariation(string s){variation = s;}

		// overloaded operators
		bool operator==(const Allele& rhs);
		bool operator!=(const Allele& rhs);

		// unit tests
		bool RunUnitTests();

};

Allele::Allele(){}

Allele::Allele(string v, string t, string sequence){
	this->variation = v;	
	this->type = t;
	this->nucleotideSequence = sequence;
}

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

void	Allele::WriteAlleleToFile(ofstream& of){

	of	  << this->variation
	  << ","
	  << this->type
	  << ","	   	  
	  << this->nucleotideSequence;
}

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

bool Allele::operator!=(const Allele& rhs){
	   return !(*this == rhs);
}

 bool Allele::RunUnitTests(){

	 bool testStatus = true;

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

	return testStatus;
}