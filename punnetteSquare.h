#pragma once 

#include <iostream>
#include <string>
#include "chromosome.h"

using namespace std;

/*----------------------------------------------------------------------------------------------------
	PunnetteSquare Class Definition

	Description: 	Creates a Punnette Square from two genes that calculates the probablity of 
					each new Allele combination
----------------------------------------------------------------------------------------------------*/


class PunnetteSquare {

	public:

		// constructors
		PunnetteSquare(){}

		PunnetteSquare(Gene a, Gene b){
			this->a = a; 
			this->b = b;
			
			this->pSquare[0][1] = a.GetAlleleA().IsDominant();
			this->pSquare[0][2] = a.GetAlleleB().IsDominant();
			this->pSquare[1][0] = b.GetAlleleA().IsDominant();
			this->pSquare[2][0] = b.GetAlleleB().IsDominant();				
		}

		// mutators
		void Reset(Gene a, Gene b){ 
			this->a = a; 
			this->b = b;
			
			this->pSquare[0][1] = a.GetAlleleA().IsDominant();
			this->pSquare[0][2] = a.GetAlleleB().IsDominant();
			this->pSquare[1][0] = b.GetAlleleA().IsDominant();
			this->pSquare[2][0] = b.GetAlleleB().IsDominant();				
		}			

		// get dominant allele
		Allele GetDominantAllele(){
			Allele dominantAllele;
			if(a.GetAlleleA().IsDominant()){
				dominantAllele = a.GetAlleleA();
			}
			else if( a.GetAlleleB().IsDominant()){
				dominantAllele = a.GetAlleleB();
			}
			else if( b.GetAlleleA().IsDominant()){
				dominantAllele = b.GetAlleleA();
			}
			else if( b.GetAlleleB().IsDominant()){
				dominantAllele = b.GetAlleleB();
			}
			return dominantAllele;
		}

		// get recessive allele
		Allele GetRecessiveAllele(){
			Allele recessiveAllele;
			if(!a.GetAlleleA().IsDominant()){
				recessiveAllele = a.GetAlleleA();
			}
			else if(!a.GetAlleleB().IsDominant()){
				recessiveAllele = a.GetAlleleB();
			}
			else if(!b.GetAlleleA().IsDominant()){
				recessiveAllele = b.GetAlleleA();
			}
			else if(!b.GetAlleleB().IsDominant()){
				recessiveAllele = b.GetAlleleB();
			}
			return recessiveAllele;
		}		

		// calculates the probablity meiosis will result in double recessive allelles
		double CalculateRecessiveProbablity(){
			int dominantSquares = 0;
			for( int i = 1; i < SIZE_OF_SQUARE; ++i ){

				for(int j = 1; j < SIZE_OF_SQUARE; ++j){
					pSquare[i][j] = pSquare[i][0] + pSquare[0][j];

					if( pSquare[i][j] > 0){
						dominantSquares++;
					}
				}
				cout << endl;
			}
			return  ((double)(SIZE_OF_SQUARE+1)-dominantSquares)/(double)(SIZE_OF_SQUARE+1);
		}

		// calculates the probablity meiosis will result in double dominant alleles
		double CalculateDominantProbablity(){
			const int DOUBLE_DOMINANT_SUM = 2;
			int totalDoubleDominant = 0;

			for( int i = 1; i < SIZE_OF_SQUARE; ++i ){

				for(int j = 1; j < SIZE_OF_SQUARE; ++j){
					pSquare[i][j] = pSquare[i][0] + pSquare[0][j];

					if( pSquare[i][j] == DOUBLE_DOMINANT_SUM){
						totalDoubleDominant++;
					}
				}
			}
			return ((double)(totalDoubleDominant)/(double)(SIZE_OF_SQUARE+1));
		}

		// calucates the probablity meiosis will result in one dominant and one recessive allele
		double CalculateDominantRecessiveProbablity(){
			const int DOMINANT_RECESSIVE_SUM = 1;
			int totalDominantRecessive = 0;
			for( int i = 1; i < SIZE_OF_SQUARE; ++i ){

				for(int j = 1; j < SIZE_OF_SQUARE; ++j){
					pSquare[i][j] = pSquare[i][0] + pSquare[0][j];

					if( pSquare[i][j] == DOMINANT_RECESSIVE_SUM){
						totalDominantRecessive++;
					}
				}
			}
			return ((double)(totalDominantRecessive)/(double)(SIZE_OF_SQUARE+1));
		}

		void PrintSquare(){
			cout << "Punnette Square" << endl;
			for( int i = 0; i < SIZE_OF_SQUARE; ++i ){
				for(int j = 0; j < SIZE_OF_SQUARE; ++j){
					cout << i << "," << j << " = " << pSquare[i][j] << " ";
				}
				cout << endl;
			}

		}

	private:
		static const int 	SIZE_OF_SQUARE = 3;
		int 				pSquare[SIZE_OF_SQUARE][SIZE_OF_SQUARE];

		Gene a;
		Gene b;

};
