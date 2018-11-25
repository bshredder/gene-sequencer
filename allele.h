/*----------------------------------------------------------------------------------------------------
	Allele class definition

	Description: represents a concrete version of a gene trait, e.g. "blue eyes"
----------------------------------------------------------------------------------------------------*/

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

enum expression_type {RECESSIVE = 0, DOMINANT = 1, NONE = 2};
const static string expression_string[] = {"recessive", "dominant", "none"};


class Allele {

	private:
		string nucleotideSequence;		// e.g. AGTC
		string type;					// e.g. Recessive
		string variation;				// e.g. Blue eyes

	public:

		// default constructor
		Allele();

		// parametized constructor
		Allele(const string& variation, const string& type, const string& sequence);

		// writes state data of this allele to filestream
		void	WriteAlleleToFile(ofstream& of);

		// returns true if Allele trait is dominant
		bool IsDominant();

		// accessor methods
		string GetNucleotide() const {return nucleotideSequence;}
		string GetExpressionType() const {return type;}
		string GetVariation() const {return variation;}	

		// mutator methods
		void SetNucleotide(const string& s) {nucleotideSequence = s;}
		void SetExpressionType(string t);
		void SetVariation(const string& s){variation = s;}

		// overloaded operators
		bool operator==(const Allele& rhs);
		bool operator!=(const Allele& rhs);

		// unit tests
		bool RunUnitTests();
};