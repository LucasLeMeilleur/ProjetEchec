﻿#include <iostream>
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
	Echiquier monEchiquier;
	monEchiquier.InitialiserEchiquier();
	char TabPromo[8] = {'t','f','c','d','T','F','C','D'};

	std::cout << "Saisir Le mode :" << '\n' << "1. Local   2. Serveur   3. Client" << '\n';
	std::cin >> mode;

	if (mode == 2) {                       // Mode Serveur
		modeServeur.Initialisation();
		modeServeur.MettreEnEcouteSurLePort(1066);
		std::cout << "En écoute" << std::endl;
		bool clienConnect = modeServeur.AttendreUnNouveauClient();
		char message[150] = "Quel est votre couleur ?";
		modeServeur.EnvoyerUnMessage(message, strlen(message));
		int n=0;
		do {

			n=modeServeur.RecevoirUnMessage(message,1500);

		}while (n<=0);


		if( message[0] == 'N') {
			std::cout << "Vous avez les blancs" << std::endl;
			bool jaiLesBlancs = true;
		}
		else{
			std::cout << "Vous avez les noirs" << std::endl;
			bool jaiLesBlancs = false;
		}

	}
	else if (mode == 3) {                    // Mode Client
		std::string IPServeur;
        char message[150];
		std::cout << "Veuillez saisir l'ip du serveur : ";
		std::cin >> IPServeur;
		modeClient.SeConnecterAUnServeur(IPServeur.c_str(), 1066);
		modeClient.Recevoir(message, 150);
		std::cout << message << std::endl;
		std::cout << "Saisir la réponse : ";
		std::cin >> message;
		modeClient.Envoyer(message, 150);
	}



	while(true){


		std::cout << monEchiquier.Les64Caracteres();
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

