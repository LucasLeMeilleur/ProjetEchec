#ifndef JoueurH
#define JoueurH



class Joueur{


	private:
	bool trait;
	int minutes;
	int seconde;

	public:
	Joueur();
	int Minutes();
	int Secondes();
	void Initialiser(int m, int s);
	void Decrementer();
	bool DefaiteAuTemps();
	void DonnerLeTrait();
	void RetirerLeTrait();

   	inline bool Trait() { return trait;};


};
#endif
