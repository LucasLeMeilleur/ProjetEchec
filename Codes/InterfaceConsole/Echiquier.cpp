﻿#include "Echiquier.h"

#include "ReglesEtNotation.h"
#include <iostream>

Echiquier::Echiquier(){
}



void Echiquier::InitialiserEchiquier(){

	//Pieces blanches
	tabEchiquier[0][0] = 't';  tabEchiquier[0][1] = 'c';
	tabEchiquier[0][2] = 'f';  tabEchiquier[0][3] = 'd';
	tabEchiquier[0][4] = 'r';  tabEchiquier[0][5] = 'f';
	tabEchiquier[0][6] = 'c';  tabEchiquier[0][7] = 't';

	//Pieces noires
	tabEchiquier[7][0] = 'T';  tabEchiquier[7][1] = 'C';
	tabEchiquier[7][2] = 'F';  tabEchiquier[7][3] = 'D';
	tabEchiquier[7][4] = 'R';  tabEchiquier[7][5] = 'F';
	tabEchiquier[7][6] = 'C';  tabEchiquier[7][7] = 'T';


	for (int j = 0; j < 8; j++) {

		tabEchiquier[1][j] = 'p';
		tabEchiquier[6][j] = 'P';
	}

	for (int i = 2; i<=5; i++){
		for (int j = 0; j < 8; j++) {

              tabEchiquier[i][j] = ' ';
		}
	}

	jBlancs.DonnerLeTrait();


}


std::string Echiquier::VisualiserEchiquier(){

	std::string str="";

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
		   str += tabEchiquier[i][j];
		}
		str = str + "\n";
	}
	return str;
}

char Echiquier::LireCaseEchiquier(int ligne, int colonne){

	return tabEchiquier[ligne][colonne];

}


void Echiquier::ModifierCaseEchiquier(char cPiece, int ligne, int colonne){

	tabEchiquier[ligne][colonne] = cPiece;


}


bool Echiquier::Deplacer(int idep, int jdep,int iarr, int jarr, char piecePromotion) {


	bool condition = ((idep >= 0 && idep <= 7) || (jdep >= 0 && jdep <= 7) || (iarr >= 0 && iarr <= 7) || (jarr >= 0 && jarr <= 7));
	bool White =  ( (jBlancs.Trait() == 1) && ((EstUnePieceBlanche(idep,jdep) == 1) && (EstUnePieceBlanche(iarr,jarr) == 0)) );
	bool Black =  ( (jNoirs.Trait() == 1) && ((EstUnePieceNoire(idep,jdep) == 1) && (EstUnePieceNoire(iarr,jarr) == 0)) );


	std::cout << "trait :" << jBlancs.Trait() << jNoirs.Trait();

	ReglesEtNotation Verif;

	if (Verif.DeplacementPossible(idep,jdep,iarr,jarr,true, this)){
		std::cout << "verification passé";

		demiCoup++;
		notation = Verif.EnregistrerNotation(idep,jdep,iarr,jarr,true, this);
		SauvegarderEchiquierPrecedent(tabEchiquier);
	}
	else{
		std::cout << "Vérification non passée, deplacement non possible\n";

		return 0;
	}

	std::cout << "Les Trois conditions : " <<  condition << White << Black;


	if ( condition && (White || Black )){

		if (((LireCaseEchiquier(idep,jdep) == 'p') && ( iarr == 7 ))     // PROMOTIONS
							||
		((LireCaseEchiquier(idep,jdep) == 'P') && ( iarr == 0 )))

		{


			if (Trait() == "noirs") {
				ModifierCaseEchiquier(std::towupper(piecePromotion),iarr,jarr);
				ModifierCaseEchiquier(' ',idep,jdep);
				demiCoup++;
				Verif.EnregistrerNotation(idep,jdep,iarr,jarr,piecePromotion,this);
				SauvegarderEchiquierPrecedent(tabEchiquier);
				return 1;
				std::cout << "Promotion";


			}
			else if (Trait() == "blancs") {


				ModifierCaseEchiquier(std::towlower(piecePromotion),iarr,jarr);
				ModifierCaseEchiquier(' ',idep,jdep);
				demiCoup++;
				Verif.EnregistrerNotation(idep,jdep,iarr,jarr,piecePromotion,this);
				SauvegarderEchiquierPrecedent(tabEchiquier);
				return 1;
			}
			else {
				std::cout << "erreur";
				return 0;
			}
			//fin condition promotions

		}


			// EN PASSANT NOIR
		else if	((idep == 3 && (LireCaseEchiquier(idep,jdep) == 'P'))
								&&
				(((LireCaseEchiquier(3,jdep-1) == 'p') && (jarr == jdep-1))
								||
				((LireCaseEchiquier(3,jdep+1) == 'p')  && (jarr == jdep+1))))
		{

			   ModifierCaseEchiquier(' ',3,jarr);
               ModifierCaseEchiquier(' ', idep, jdep);
			   ModifierCaseEchiquier('P', iarr, jarr);

			   std::cout << "En passant noir";
			   demiCoup++;
			   Verif.EnregistrerNotation(idep,jdep,iarr,jarr,' ',this);
			   SauvegarderEchiquierPrecedent(tabEchiquier);
			   return 1;
		}



			// EN PASSANT BLANC
		else if	((idep == 4 && (LireCaseEchiquier(idep,jdep) == 'p'))
								&&
				( (( LireCaseEchiquier(4,jdep-1) == 'P') && (jarr == jdep-1))
								||
				((LireCaseEchiquier(4,jdep+1) == 'P')  && (jarr == jdep+1))) )
		{




			   std::cout << "En passant noir";
				ModifierCaseEchiquier(' ',4,jarr);
				ModifierCaseEchiquier(' ', idep, jdep);
				ModifierCaseEchiquier('p', iarr, jarr);

				SauvegarderEchiquierPrecedent(tabEchiquier);
				Verif.EnregistrerNotation(idep,jdep,iarr,jarr,' ',this);
				demiCoup++;

				return 1;
		}



		
		else{

			char piece = LireCaseEchiquier(idep,jdep);
			ModifierCaseEchiquier(piece,iarr,jarr);
			ModifierCaseEchiquier(' ',idep,jdep);
			if (piecePromotion != ' ') ModifierCaseEchiquier(piecePromotion,iarr,jarr);
			std::cout << "Deplacement basique reussi " << std::endl;

			Verif.EnregistrerNotation(idep,jdep,iarr,jarr,' ',this);
			SauvegarderEchiquierPrecedent(tabEchiquier);
			demiCoup++;
			return 1;

		}

	}


	// LES ROCKS
	else if ( (((LireCaseEchiquier(idep,jdep) == 'R') && (LireCaseEchiquier(iarr,jarr) == 'T')) ||     //Rocks Noirs
			((LireCaseEchiquier(iarr,jarr) == 'R') && (LireCaseEchiquier(idep,jdep) == 'T')))
							||

			(((LireCaseEchiquier(idep,jdep) == 'r') && (LireCaseEchiquier(iarr,jarr) == 't')) ||     //Rocks Blancs
			((LireCaseEchiquier(iarr,jarr) == 'r') && (LireCaseEchiquier(idep,jdep) == 't'))))

		{

					   //Grand Rock noir
					if((((idep == 7 && jdep == 0) && (iarr == 7 && jarr == 4))     ||  ((idep ==7 && jdep == 4) && (iarr == 7 && jarr == 0)))   //Verification des emplacements des pieces
															&&
					( ((LireCaseEchiquier(7,1) == ' ') && (LireCaseEchiquier(7,2) == ' ') && (LireCaseEchiquier(7,3) == ' ')))) //Verification des case libres
					{

					std::cout << "grand rock noir";


					ModifierCaseEchiquier(' ',7,4);
					ModifierCaseEchiquier('R',7,2);
					ModifierCaseEchiquier(' ',7,0);
					ModifierCaseEchiquier('T',7,3);
					Verif.EnregistrerNotation(idep,jdep,iarr,jarr,' ',this);
					SauvegarderEchiquierPrecedent(tabEchiquier);
					demiCoup++;
					 return 1;
					}


					// Petit Rock noir
					else if((((idep == 7 && jdep == 7) && (iarr == 7 && jarr == 4)) ||  ((idep ==7 && jdep == 4) && (iarr == 7 && jarr == 7)))   //Verification des emplacements des pieces
															&&
					( ((LireCaseEchiquier(7,5) == ' ') && (LireCaseEchiquier(7,6) == ' ')))) //Verification des case libres
					{

					std::cout << "petit rock noir";

					ModifierCaseEchiquier(' ',7,4);
					ModifierCaseEchiquier('R',7,6);
					ModifierCaseEchiquier(' ',7,7);
					ModifierCaseEchiquier('T',7,5);
					Verif.EnregistrerNotation(idep,jdep,iarr,jarr,' ',this);
					SauvegarderEchiquierPrecedent(tabEchiquier);
					demiCoup++;
					 return 1;
					}



					 //Grand Rock blanc
					else if((((idep == 0 && jdep == 0) && (iarr == 0 && jarr == 4))     ||  ((idep ==0 && jdep == 4) && (iarr == 0 && jarr == 0)))   //Verification des emplacements des pieces
															&&
					( ((LireCaseEchiquier(0,1) == ' ') && (LireCaseEchiquier(0,2) == ' ') && (LireCaseEchiquier(0,3) == ' ')))) //Verification des case libres
					{

					std::cout << "petit rock blanc";


					ModifierCaseEchiquier(' ',0,4);
					ModifierCaseEchiquier('r',0,2);
					ModifierCaseEchiquier(' ',0,0);
					ModifierCaseEchiquier('t',0,3);
					Verif.EnregistrerNotation(idep,jdep,iarr,jarr,' ',this);
					SauvegarderEchiquierPrecedent(tabEchiquier);
					demiCoup++;
					return 1;

					// Petit Rock blanc
					}

					else if((((idep == 0 && jdep == 7) && (iarr == 0 && jarr == 4)) ||  ((idep ==0 && jdep == 4) && (iarr == 0 && jarr == 7)))   //Verification des emplacements des pieces
															&&
					( ((LireCaseEchiquier(0,5) == ' ') && (LireCaseEchiquier(0,6) == ' ')))) //Verification des case libres
					{

					std::cout << "petit rock blanc" << std::endl;
					ModifierCaseEchiquier(' ',0,4);
					ModifierCaseEchiquier('r',0,6);
					ModifierCaseEchiquier(' ',0,7);
					ModifierCaseEchiquier('t',0,5);

					Verif.EnregistrerNotation(idep,jdep,iarr,jarr,' ',this);
					SauvegarderEchiquierPrecedent(tabEchiquier);
					demiCoup++;
					return 1;

					}
		}
	else{
		std::cout << "Deplacement impossible "<< std::endl;
		return 0;

	}

    return 0;
}





void Echiquier::ChangerLeTrait(){

	bool Blanc = jBlancs.Trait();
	bool Noir = jNoirs.Trait();

	if(Blanc == 1){
		jBlancs.RetirerLeTrait();
		jNoirs.DonnerLeTrait();
	}
	else if(Noir == 1){
		jNoirs.RetirerLeTrait();
		jBlancs.DonnerLeTrait();
	}


}


std::string Echiquier::Trait(){

	if (jBlancs.Trait() == 1) {
		return "blancs";
	}
	else if (jNoirs.Trait() == 1) {
		return "noirs";
	}
    return "erreur attribution trait";
}

bool Echiquier::EstVide(int ligne, int colonne){
	if (tabEchiquier[ligne][colonne] == ' ') {
        return 1;
	}
	else return 0;

}

bool Echiquier::EstUnePieceBlanche(int ligne, int colonne){
	if ( tabEchiquier[ligne][colonne] == ' ') return 0;
	else if (std::islower(tabEchiquier[ligne][colonne])) return 1;
	else return 0;
}



bool Echiquier::EstUnePieceNoire(int ligne, int colonne){

	if ( tabEchiquier[ligne][colonne] == ' ') return 0;
	else if (std::isupper(tabEchiquier[ligne][colonne])) return 1;
	else return 0;
}



std::string Echiquier::Les64Caracteres(){

	std::string TableStr;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			TableStr += tabEchiquier[i][j];
		}
	}

	return TableStr;

}

void Echiquier::ChargerEchiquierComplet(char * les64Caracteres){

	int k = 0;
	for(int i = 0; i < 8 ; i++){
		for(int j = 0; j < 8 ; j++){
			tabEchiquier[i][j] = les64Caracteres[k];
			k++;
		}
	}
}

void Echiquier::SauvegarderEchiquierPrecedent(char tEchiquier[8][8]){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tabEchiquierPrecedent[i][j] = tEchiquier[i][j];
		}
	}
}



