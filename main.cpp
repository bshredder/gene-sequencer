/*  Class:      	CSC 1810 
    Project:    	Homework Project #5
	Descripiton
	Learning:		Declaring, defining, and using classes
*/

#include <iostream>
#include <string>
#include <cassert>
#include <vector> 
#include <iomanip>
#include "gene.h"
#include "chromosome.h"
#include "geneSequencer.h"

using namespace std;


/*----------------------------------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

    cout << "Gene Sequencer - Program #5" << endl << endl;

	GeneSequencer sequencer;
	sequencer.PowerOnSelfTest();
	sequencer.Run();

    return 0;
}


