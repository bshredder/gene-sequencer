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

enum choice_type { CREATE = 1, ANALYZE, INPUT, OUTPUT, EXIT};

/*----------------------------------------------------------------------------------------------------
	Function Declarations
----------------------------------------------------------------------------------------------------*/

int MenuChoice();

/*----------------------------------------------------------------------------------------------------
	Main
----------------------------------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

    cout << "Gene Sequencer - Program #5" << endl << endl;

	GeneSequencer sequencer;
	ChromosomePair newChromosome;
	int curSelection = EXIT;

	do {
		curSelection = MenuChoice();	

		switch(curSelection){

			case CREATE:
				newChromosome = sequencer.CreateChromosomePair();
				break;
			case ANALYZE:
				sequencer.SequenceChromosomePair(newChromosome);
				break;
			case INPUT:
				newChromosome = sequencer.ImportChromosomePair();
				break;
			case OUTPUT:
				sequencer.ExportChromosomePair(newChromosome);
				break;
			case EXIT:
				break;
			default:
				cout << "ERROR: Invalid Selection" << endl;
				break;
		}
	} while( curSelection != EXIT );

    // Just pause
    {
        char c;
        cout << "Hit enter to exit:";
        cin.get(c); 
    }
    return 0;
}

/*----------------------------------------------------------------------------------------------------
	MenuChoice - gets user choice
----------------------------------------------------------------------------------------------------*/
int MenuChoice(){

	// TODO add color and alignment
	int choice = EXIT;
	cout << left << setw(15) << "\033[1;31mMENU\033[0m\n";
	cout << right << setfill('-') << setw(30) << "" << endl;	
	cout << left << " 1. Create ChromosomePair " << endl;
	cout << " 2. Analyze ChromosomePair " << endl;
	cout << " 3. Input ChromosomePair from file " << endl;
	cout << " 4. Output ChromosomePair to file " << endl;
	cout << " 5. Exit " << endl; 
	cout << right << setfill('-') << setw(30) << "" << endl;		
	cout << "Please enter your choice (1-5) ";
	cout << setfill(' ');	
	cin >> choice;

	return choice;
}
