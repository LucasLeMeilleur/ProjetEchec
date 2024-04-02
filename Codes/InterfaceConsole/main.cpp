#include <iostream>

#include <conio.h>
#include "Echiquier.h"
#include <Windows.h>


int main(){


	Echiquier monEchiquier;
	monEchiquier.InitialiserEchiquier();
	monEchiquier.ModifierCaseEchiquier(' ',7,0);
	monEchiquier.ModifierCaseEchiquier(' ',6,0);
	monEchiquier.ModifierCaseEchiquier('p',6,0);




	char TabPromo[8] = {'t','f','c','d','T','F','C','D'};

	while(true){

		std::cout << monEchiquier.VisualiserEchiquier();


		int idep,jdep,iarr,jarr;
		char pieceDemande;
		bool test;
		bool TestCarac = false;




		std::cout << "Trait aux : " << monEchiquier.Trait() << "\n";
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



		if(((monEchiquier.LireCaseEchiquier(idep, jdep) == 'p') && iarr == 7)
					||
		((monEchiquier.LireCaseEchiquier(idep, jdep) == 'P') && iarr == 0)) {


			std::cout << "Quel est votre piece pour la promotion : ";
			std::cin >> pieceDemande;

			for (int i = 0; i < 8; i++) {
				if(pieceDemande == TabPromo[i]) {
                    TestCarac = true;
					break;
                }


			}

			if (TestCarac) test = monEchiquier.Deplacer(idep,jdep,iarr,jarr,pieceDemande);
		}
		else test =  monEchiquier.Deplacer(idep,jdep,iarr,jarr,' ');




		std::cout << "valeur de test : " << test << std::endl;



		if (test == 1) {
			std::cout << "Coup Reussi" << std::endl;
			monEchiquier.ChangerLeTrait();

		}
		else std::cout << "Coup illegal" << std::endl;
		Sleep(2500);
		clrscr();
	}
	std::cin.get();
	Sleep(2500);
	return 0;
}
