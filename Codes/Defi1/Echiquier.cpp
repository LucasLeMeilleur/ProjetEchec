#include "Echiquier.h"

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
	bool White =  ( (jBlancs.Trait() == 1) && (EstUnePieceBlanche(idep,jdep) == 1) && (EstUnePieceBlanche(iarr,jarr) == 0));
	bool Black =  ( (jNoirs.Trait() == 1) && (EstUnePieceNoir(idep,jdep) == 1) && (EstUnePieceNoir(iarr,jarr) == 0));


	if ( condition && (White || Black )){
        char piece = LireCaseEchiquier(idep,jdep);
		ModifierCaseEchiquier(piece,iarr,jarr);
		ModifierCaseEchiquier(' ',idep,jdep);

		if (piecePromotion != ' ') ModifierCaseEchiquier(piecePromotion,iarr,jarr);


		std::cout << "Deplacement reussi " << std::endl;
		return 1;
	}

 	else {return 0;std::cout << "Deplacemen impossible "<< std::endl;}

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
    return "erreur";
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



bool Echiquier::EstUnePieceNoir(int ligne, int colonne){

	if (std::isupper(tabEchiquier[ligne][colonne])) return 1;
	else return 0;
}