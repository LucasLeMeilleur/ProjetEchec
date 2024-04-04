#include <iostream>
#include <string>
#include <string.h>
#include <conio.h>
#include <Windows.h>


#include "Echiquier.h"
#include "SNClientTCP.h"
#include "SNServeurTcpMonoClient.h"


int main(){


	int mode;
	SNClientTCP modeClient;
	SNServeurTcpMonoClient modeServeur;
	std::cin >> mode;

	if (mode == 2) {
		modeServeur.Initialisation();
		modeServeur.MettreEnEcouteSurLePort(1066);
		std::cout << "En écoute";
		bool clienConnect = modeServeur.AttendreUnNouveauClient();
		std::cout << "Quel est votre couleur ?" << std::endl;
		std::string message = "Quel est votre couleur ?";
		modeServeur.EnvoyerUnMessage(const_cast<char*>(message.data()), message.length()-1);

		modeServeur.RecevoirUnMessage(const_cast<char*>(message.data()),150);

		if( message[0] == 'N') {
			std::cout << "Vous avez les blancs" << std::endl;
			bool jaiLesBlancs = true;
		}
		else{
			std::cout << "Vous avez les noirs" << std::endl;
			bool jaiLesBlancs = false;
		}



	}
	else if (mode == 3) {

		std::string IPServeur;
        std::string message = "";


		std::cout << "Veuillez saisir l'ip du serveur : ";
		std::cin >> IPServeur;
		modeClient.SeConnecterAUnServeur(IPServeur, 1066);
		modeClient.Recevoir(const_cast<char*>(message.data()), 150);
		std::cout << message << std::endl;
		std::cout << "Saisir la réponse : ";
		std::cin >> message;
		modeClient.Envoyer(message.c_str(), message.length()-1);
	}








































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


	if(mode == 2){

		modeServeur.FermerLaCommunicationAvecLeClient();
        modeServeur.ArreterLeServeur();
	}




	return 0;






}

