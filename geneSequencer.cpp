
#include "geneSequencer.h"


using namespace std;


/*----------------------------------------------------------------------------------------------------
	CreateChromosomePair

	Description:	Queries the user for basic information needed to create a complete chromosome
					Creates and returns a chromosome pair object 
----------------------------------------------------------------------------------------------------*/

ChromosomePair 	GeneSequencer::CreateChromosomePair(){
	
	char moreGenes = 'n';					
	ChromosomePair newChromosome;
	
	do {
			string name;
			string trait;
			string type;
			string sequence;
			string variant;


			cout << "What is the gene name? (e.g. TZ458)";
			cin >> name;
			cout << "What is the gene trait? (e.g. eye color)";
			cin >> trait;
			cout << "What is allele 1 variant? (e.g. blue/brown/etc.)";
			cin >> variant;
			cout << "What is allele 1 Type? (e.g. dominant/recessive)";
			cin >> type;
			cout << "What is allele 1 nucleotide sequence? (e.g. AGTC)";
			cin >> sequence;
			Allele alleleA(variant, type, sequence);

			cout << "What is allele 2 variant? (e.g. blue/brown/etc.)";
			cin >> variant;
			cout << "What is allele 2 Type? (e.g. dominant/recessive)";
			cin >> type;
			cout << "What is allele 2 nucleotide sequence? (e.g. AGTC)";
			cin >> sequence;
			Allele alleleB(variant, type, sequence);

			Gene newGene(alleleA, alleleB);
			newGene.SetTrait(trait);
			newGene.SetName(name); 
			newChromosome.AddGene(newGene);

			cout << "Would you like to add a new gene? (y/n)" << endl;
			cin >> moreGenes;

		} while (moreGenes == 'y');

		return newChromosome;
}

/*----------------------------------------------------------------------------------------------------
	DisplayUserMenu()

	Description:	Displays the user interface (menu) to the user
					Returns the user's selection
----------------------------------------------------------------------------------------------------*/

int GeneSequencer::DisplayUserMenu(){
	
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



/*----------------------------------------------------------------------------------------------------
	Run()

	Description:	Presents menu until user selects exit. 
					Calls the appropriate method based on user choice
----------------------------------------------------------------------------------------------------*/

void GeneSequencer::Run(){

	int curSelection = EXIT;

	do {
		curSelection = this->DisplayUserMenu();	

		switch(curSelection){

			case CREATE:
				this->c = this->CreateChromosomePair();
				break;
			case ANALYZE:
				this->SequenceChromosomePair(this->c);
				break;
			case INPUT:
				this->c = this->ImportChromosomePair();
				break;
			case OUTPUT:
				this->ExportChromosomePair(this->c);
				break;
			case EXIT:
				break;
			default:
				cout << "ERROR: Invalid Selection" << endl;
				break;
		}
	} while( curSelection != EXIT );
}

ChromosomePair 	GeneSequencer::ImportChromosomePair(const string& fileName){
	
	string fn;	
	if( !fileName.empty()){
		fn = fileName;;
	}
	else{
		cin.clear();
		cout << "Enter filename to input chromosome data from: ";
		cin >> fn;
	}

	ChromosomePair c;
	ifstream file( fn );
	c.InputFromFile(file);
	file.close();
	return c;
}

void 	GeneSequencer::ExportChromosomePair(ChromosomePair c, const string& fileName){

	string fn;
	if(!fileName.empty() ){
		fn = fileName;
	}
	else{
		cin.clear();
		cout << "Enter filename to output chromosome data to: ";
		cin >> fn;
	}
	ofstream myfile;
	myfile.open (fn, std::ios_base::app);
	c.OutputToFile(myfile);
	myfile.close();
}
ChromosomePair 	GeneSequencer::DoMeiosis(ChromosomePair x, ChromosomePair y){
	return x + y;
}

void GeneSequencer::SequenceChromosomePair(ChromosomePair c){
	c.AnalyzeGenotype();
}

bool GeneSequencer::PowerOnSelfTest(){

	bool testStatus = true;

	Allele testAllele;
	if(false == testAllele.RunUnitTests() ) {
		cout << "POST ERROR - Allele unit tests" << endl;
		testStatus = false;
	}

	Gene testGene;
	if(false == testGene.RunUnitTests() ){
		cout << "POST ERROR - Gene unit tests" << endl;
		testStatus = false;		
	}

	ChromosomePair testChromosome;
	if(false == testChromosome.RunUnitTests() ){
		cout << "POST ERROR - Chromosome unit tests" << endl;
		testStatus = false;		
	}

	return testStatus;
}