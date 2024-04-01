#include <iostream>

#include <conio.h>
#include "Echiquier.h"
#include <Windows.h>


int main(){


	Echiquier monEchiquier;
	monEchiquier.InitialiserEchiquier();
	monEchiquier.ModifierCaseEchiquier('p',3,2);
	monEchiquier.ModifierCaseEchiquier('P',3,3);
	while(true){

		std::cout << monEchiquier.VisualiserEchiquier();


		int idep,jdep,iarr,jarr;
		char pieceDemande;
		bool test;



		std::cout << "Trait aux ����: " << monEchiquier.Trait() << "\n";
		std::cout << "idep : ";
		std::cin >> idep;
		std::cout << "jdep : ";
		std::cin >> jdep;
		std::cout << "iarr : ";
		std::cin >> iarr;
		std::cout << "jarr : ";
		std::cin >> jarr;

		if (idep <= -1 || jdep <= -1 || iarr <= -1 || jarr <= -1) break;
		if (idep >= 8 || jdep >= 8 || iarr >= 8 || jarr >= 8) break;






		if (((monEchiquier.LireCaseEchiquier(idep,jdep) == 'p') && ( iarr == 7 )  )     // PROMOTIONS
                            ||
		((monEchiquier.LireCaseEchiquier(idep,jdep) == 'P') && ( iarr == 0 )) ){


			if (monEchiquier.Trait() == "noirs") {
				std::cout << "Quel piece voulez vous :";
				std::cin >> pieceDemande;
				test = monEchiquier.Deplacer(idep,jdep,iarr,jarr,std::towupper(pieceDemande));
			}
			else if (monEchiquier.Trait() == "blancs") {
				std::cout << "Quel piece voulez vous :";
				std::cin >> pieceDemande;
				test = monEchiquier.Deplacer(idep,jdep,iarr,jarr,std::towlower(pieceDemande));
			}
			else std::cout << "erreur";




		}

		// EN PASSANT NOIR
		else if	((idep == 3 && (monEchiquier.LireCaseEchiquier(idep,jdep) == 'P'))
								&&
				(((monEchiquier.LireCaseEchiquier(3,jdep-1) == 'p') && (jarr == jdep-1))
								||
				((monEchiquier.LireCaseEchiquier(3,jdep+1) == 'p')  && (jarr == jdep+1))))
		{
			   test = monEchiquier.Deplacer(idep,jdep,iarr,jarr,' ');
               monEchiquier.ModifierCaseEchiquier(' ',3,jarr);
		}



        // EN PASSANT BLANC
		else if	((idep == 4 && (monEchiquier.LireCaseEchiquier(idep,jdep) == 'p'))
								&&
				( (( monEchiquier.LireCaseEchiquier(4,jdep-1) == 'P') && (jarr == jdep-1))
								||
				((monEchiquier.LireCaseEchiquier(4,jdep+1) == 'P')  && (jarr == jdep+1))) )
		{

				std::cout << "Condition valide "<< std::endl;

               monEchiquier.ModifierCaseEchiquier(' ',4,jarr);
			   test = monEchiquier.Deplacer(idep,jdep,iarr,jarr,' ');

		}

		else test = monEchiquier.Deplacer(idep,jdep,iarr,jarr,' ');










		// LES ROCKS

		if ( (((monEchiquier.LireCaseEchiquier(idep,jdep) == 'R') && (monEchiquier.LireCaseEchiquier(iarr,jarr) == 'T')) ||     //Rocks Noirs
			((monEchiquier.LireCaseEchiquier(iarr,jarr) == 'R') && (monEchiquier.LireCaseEchiquier(idep,jdep) == 'T')))
							||

			(((monEchiquier.LireCaseEchiquier(idep,jdep) == 'r') && (monEchiquier.LireCaseEchiquier(iarr,jarr) == 't')) ||     //Rocks Blancs
			((monEchiquier.LireCaseEchiquier(iarr,jarr) == 'r') && (monEchiquier.LireCaseEchiquier(idep,jdep) == 't')))




			){

			   //Grand Rock noir
			if((((idep == 7 && jdep == 0) && (iarr == 7 && jarr == 4))     ||  ((idep ==7 && jdep == 4) && (iarr == 7 && jarr == 0)))   //Verification des emplacements des pieces
													&&
			( ((monEchiquier.LireCaseEchiquier(7,1) == ' ') && (monEchiquier.LireCaseEchiquier(7,2) == ' ') && (monEchiquier.LireCaseEchiquier(7,3) == ' ')))) //Verification des case libres
			{

			std::cout << "pass�";
			test = monEchiquier.Deplacer(7,4,7,2,' ');
			test = monEchiquier.Deplacer(7,0,7,3,' ');

			}


			// Petit Rock noir
			else if((((idep == 7 && jdep == 7) && (iarr == 7 && jarr == 4)) ||  ((idep ==7 && jdep == 4) && (iarr == 7 && jarr == 7)))   //Verification des emplacements des pieces
													&&
			( ((monEchiquier.LireCaseEchiquier(7,5) == ' ') && (monEchiquier.LireCaseEchiquier(7,6) == ' ')))) //Verification des case libres
			{

			std::cout << "pass�";
			test = monEchiquier.Deplacer(7,4,7,6,' ');
			test = monEchiquier.Deplacer(7,7,7,5,' ');

			}



             //Grand Rock blanc
			else if((((idep == 0 && jdep == 0) && (iarr == 0 && jarr == 4))     ||  ((idep ==0 && jdep == 4) && (iarr == 0 && jarr == 0)))   //Verification des emplacements des pieces
													&&
			( ((monEchiquier.LireCaseEchiquier(0,1) == ' ') && (monEchiquier.LireCaseEchiquier(0,2) == ' ') && (monEchiquier.LireCaseEchiquier(0,3) == ' ')))) //Verification des case libres
			{

			std::cout << "pass�";
			test = monEchiquier.Deplacer(0,4,0,2,' ');
			test = monEchiquier.Deplacer(0,0,0,3,' ');
			// Petit Rock blanc
			}

			else if((((idep == 0 && jdep == 7) && (iarr == 0 && jarr == 4)) ||  ((idep ==0 && jdep == 4) && (iarr == 0 && jarr == 7)))   //Verification des emplacements des pieces
													&&
			( ((monEchiquier.LireCaseEchiquier(0,5) == ' ') && (monEchiquier.LireCaseEchiquier(0,6) == ' ')))) //Verification des case libres
			{

			std::cout << "pass�" << std::endl;
			test = monEchiquier.Deplacer(0,4,0,6,' ');
			test = monEchiquier.Deplacer(0,7,0,5,' ');

			}
		}







		std::cout << "valeur de test : " << test << std::endl;



		if (test == 1) {
			std::cout << "Coup Reussi" << std::endl;
			monEchiquier.ChangerLeTrait();

		}
		else std::cout << "Coup illegal" << std::endl;
		Sleep(5000);
		clrscr();
	}
	std::cin.get();
	Sleep(2500);
	return 0;
}
