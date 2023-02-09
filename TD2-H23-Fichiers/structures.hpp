#include <iostream>

using namespace std;

struct Film; struct Acteur;

class ListeFilms {
public:
	ListeFilms() { //Constructeur par defaut
		capacite = 0;
		nElements = 0;
		elements = {};
	}

	ListeFilms(string nomFichier) {
		capacite = creerListe(nomFichier).capacite;
		nElements = creerListe(nomFichier).nElements;
		elements = creerListe(nomFichier).elements;
	}

	ListeFilms creerListe(string nomFichier);
	void ajouterFilm(Film* film);
	void enleverFilm(Film* filmAEnlever);
	Acteur* trouverActeur(const string& nomActeur);
	void detruire();
	void afficher() const;
	void afficherFilmographieActeur(const string& nomActeur);


	int getCapacite() {
		return capacite;
	}
	void setCapacite(int c) {
		capacite = c;
	}

	int getnElements() {
		return nElements;
	}
	void setnElements(int n) {
		nElements = n;
	}

	Film** getElements() {
		return elements;
	}
	void setElements(Film** e) {
		elements = e;
	}

private:
	int capacite, nElements;
	Film** elements;
};

struct ListeActeurs {
	int capacite, nElements;
	Acteur** elements;
};

struct Film
{
	std::string titre, realisateur; 
	int anneeSortie, recette; 
	ListeActeurs acteurs;
};

struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};