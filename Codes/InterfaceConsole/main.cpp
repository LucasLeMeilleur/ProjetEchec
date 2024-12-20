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
	bool  abandon=false,coupillegal=false;
	SNClientTCP modeClient;
	SNServeurTcpMonoClient modeServeur;
	Echiquier monEchiquier;
	monEchiquier.InitialiserEchiquier();
	std::cout << monEchiquier.LireCaseEchiquier(5,5);
	char TabPromo[8] = {'t','f','c','d','T','F','C','D'};
	bool jaiLesBlancs;
	std::cout << "Saisir Le mode :" << '\n' << "1. Local   2. Serveur   3. Client" << '\n';
	std::cin >> mode;

	if (mode == 2) {                       // Mode Serveur
		modeServeur.Initialisation();
		modeServeur.MettreEnEcouteSurLePort(1066);
		std::cout << "En écoute \n";
		bool clienConnect = modeServeur.AttendreUnNouveauClient();
		char message[150] = "Quel est votre couleur ?";
		modeServeur.EnvoyerUnMessage(message, strlen(message));
		int n=0;
		do {

			n=modeServeur.RecevoirUnMessage(message,1500);

		}while (n<=0);


		if( message[0] == 'N') {
			std::cout << "Vous avez les blancs \n";
			jaiLesBlancs = true;
		}
		else{
			std::cout << "Vous avez les noirs \n";
			jaiLesBlancs = false;
		}

	}
	else if (mode == 3) {                    // Mode Client
		std::string IPServeur;
        char message[150];
		std::cout << "Veuillez saisir l'ip du serveur : \n";
		std::cin >> IPServeur;
		modeClient.SeConnecterAUnServeur(IPServeur.c_str(), 1066);
		modeClient.Recevoir(message, 150);
		std::cout << message << std::endl;
		std::cout << "Saisir la réponse : ";
		std::cin >> message;
		if(strcmp(message,"N") == 0) jaiLesBlancs = false;
		else jaiLesBlancs = true;
		modeClient.Envoyer(message, 150);
	}



	do{
		std::cout << "\n\nexecution de la boucle principale\n";
		char message[150];
		std::string couleur = monEchiquier.Trait();
		std::cout << "Le mode : " << mode << "\n";
		std::cout << "  Le trait est aux : " << couleur << "\n";
		std::cout << " Est ce que tu as la couleur blanche ? " << jaiLesBlancs << "\n";


		if(  (jaiLesBlancs == true && couleur=="blancs") || (jaiLesBlancs == false && couleur == "noirs") || (mode == 1)){

			// Deplacement du main ?

			int idep,jdep,iarr,jarr;
			bool test;
			char pieceDemande;
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

			while( (coupillegal == false) && (abandon == false)){

            	std::cout << "Demarrage boucle de jeu \n";
				std::cout << monEchiquier.VisualiserEchiquier();
				if( idep == -1){
					std::cout << "idep est inferieur a 1 processus d'abandon \n";
					abandon = true;
					if(mode == 2) modeServeur.EnvoyerUnMessage( "Abandon", 150);
					if(mode == 3) modeClient.Envoyer("Abandon", 150);
				}
				else{

					if(((monEchiquier.LireCaseEchiquier(idep, jdep) == 'p') && iarr == 7) ||
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

					coupillegal =  !(monEchiquier.Deplacer(idep,jdep,iarr,jarr,' '));
					std::cout << "bvaleur de coup illégale : " << coupillegal << "\n";

					if(coupillegal){
						std::cout << "Coup illégal, deplacement non effectué \n" ;

					}
					else{
						std::string position = monEchiquier.Les64Caracteres();
						if(mode == 2) modeServeur.EnvoyerUnMessage((char*)position.c_str(),64);
						if(mode == 3) modeClient.Envoyer((char*)position.c_str(), 64);
						monEchiquier.ChangerLeTrait();
						std::cout << "Coup non illégale, envoyé \n";
						break;
					}
				}
			}
		}
		else{


			int n = 0;
			do{
				if(mode == 2) n =modeServeur.RecevoirUnMessage(message,150);
				if(mode == 3) n =modeClient.Recevoir(message,150);
			}while(n<0);

            std::cout << "Message reçu : " << message << "\n";

			if(strcmp(message, "Abandon") == 0){
				std::cout << "Votre adversaire abandonne \n";
				abandon = true;
			}
			else{
				monEchiquier.ChargerEchiquierComplet(message);
				monEchiquier.ChangerLeTrait();
			}
		}


		Sleep(2500);


	}while(!abandon);

	std::cout << "\nsortie de la boucle abandon \n";

	Sleep(2500);

	if(mode == 2){

		modeServeur.FermerLaCommunicationAvecLeClient();
        modeServeur.ArreterLeServeur();
	}




	std::cin.get();






}

