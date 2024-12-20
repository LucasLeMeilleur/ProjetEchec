
#ifndef ECHIQUIER_H
#define ECHIQUIER_H

#include "Joueur.h"
#include <string>


class Echiquier{


	private:

	Joueur jNoirs;
	Joueur jBlancs;
	char tabEchiquier[8][8];
	int demiCoup;
	char tabEchiquierPrecedent[8][8];
	bool grandRoqueNoirPossible;
	bool petitRoqueNoirPossible;
	bool grandRoqueBlancPossible;
	bool petitRoqueBlancPossible;
	std::string notation;

	public:
	Echiquier();
	char LireCaseEchiquier(int ligne, int colonne);
	void InitialiserEchiquier();
	std::string VisualiserEchiquier();
	std::string Les64Caracteres();
	void ChargerEchiquierComplet(char * les64Caracteres);
	void ModifierCaseEchiquier(char cPiece, int ligne, int colonne);
	bool EstUnePieceNoire(int ligne, int colonne);
	bool EstUnePieceBlanche(int ligne , int colonne);
	bool EstVide(int ligne, int colonne);
	void ChangerLeTrait();
	bool Deplacer(int idep, int jdep,int iarr, int jarr, char piecePromotion);
	std::string Trait();
	void SauvegarderEchiquierBMP(char * Fichier);

	void SauvegarderEchiquierPrecedent(char tEchiquier[8][8]);
	inline std::string Notation(){ return notation;};
	inline int DemiCoup(){return demiCoup;};
	inline void GrandRoqueNoirImpossible(){ grandRoqueNoirPossible=false;};
	inline void PetitRoqueNoirImpossible(){ petitRoqueNoirPossible=false;};
	inline void GrandRoqueBlancImpossible(){ grandRoqueBlancPossible = false;};
	inline void PetitRoqueBlancImpossible(){ petitRoqueBlancPossible = false;};
	inline bool GrandRoqueNoirPossible(){ return grandRoqueNoirPossible;};
	inline bool PetitRoqueNoirPossible(){ return petitRoqueNoirPossible;};
	inline bool GrandRoqueBlancPossible(){ return grandRoqueBlancPossible;};
	inline bool PetitRoqueBlancPossible(){ return petitRoqueBlancPossible;};

	inline char LireCaseEchiquierPrecedent(int ligne, int colonne){ return tabEchiquierPrecedent[ligne][colonne];};

};

#endif
