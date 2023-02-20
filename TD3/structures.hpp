/*
nom: structures.hpp
description: Contient les definitions des structures et de la classe ListeFilms
auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
date: 12 fevrier 2023
*/

#include <iostream>
#include <memory>

using namespace std;

struct Film;
struct Acteur;

class ListeFilms {
public:
	ListeFilms() { //Constructeur par defaut
		capacite_ = 0;
		nElements_ = 0;
		elements_ = {};
	}

	ListeFilms(string nomFichier) {
		ListeFilms temp = creerListe(nomFichier);
		capacite_ = temp.capacite_;
		nElements_ = temp.nElements_;
		elements_ = temp.elements_;
	}

	ListeFilms creerListe(string nomFichier);
	void ajouterFilm(Film* film);
	void enleverFilm(Film* filmAEnlever);
	shared_ptr<Acteur> trouverActeur(const string& nomActeur);
	void detruire();
	void afficher() const;
	void afficherFilmographieActeur(const string& nomActeur) ;
	int getnElements();
	Film** getElements();

	Film* operator[](int index)
	{
		return elements_[index];
	}
private:
	int capacite_, nElements_;
	Film** elements_;
};


struct ListeActeurs
{
	int capacite, nElements;
	unique_ptr<shared_ptr<Acteur>[]> elements;
	ListeActeurs()
	{
		capacite = 0;
		nElements = 0;
		elements = make_unique<shared_ptr<Acteur>[]>(0);
	}
	ListeActeurs(const ListeActeurs& liste) 
	{
        capacite = liste.capacite;
        nElements = liste.nElements;
        elements = make_unique<shared_ptr<Acteur>[]>(capacite);
        for (int i = 0; i < nElements; i++) {
            elements[i] = liste.elements[i];
        }
    }
	ListeActeurs(unsigned int cap, int n)
	{
		capacite = cap;
		nElements = n;
		elements = make_unique<shared_ptr<Acteur>[]>(n);
	}
	friend ostream& operator<<(ostream& os, const Acteur& acteur);

};

struct Film
{
	std::string titre, realisateur;
	int anneeSortie, recette;
	ListeActeurs acteurs;
	Film()
	{
		titre = "";
		realisateur = "";
		anneeSortie = 0;
		recette = 0;
	}
	Film(unsigned int capacite, int nElements, string t, string rea, int ann, int rec)
	{
		acteurs = ListeActeurs(capacite, nElements);
		titre = t;
		realisateur = rea;
		anneeSortie = ann;
		recette = rec;
	}

	friend ostream& operator<<(ostream& os, const Film& film);
};

struct Acteur
{
	std::string nom ;
	int anneeNaissance ;
	char sexe ;
	// ListeFilms joueDans;
};