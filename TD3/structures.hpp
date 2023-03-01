/*
nom: structures.hpp
description: Contient les definitions des structures et de la classe ListeFilms
auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
date: 12 fevrier 2023
*/

#include <iostream>
#include <memory>
#include <fstream>
#include "cppitertools/range.hpp"
#include "gsl/span"

using namespace iter;
using namespace std;
using namespace gsl;

typedef uint16_t UInt16;

UInt16 lireUint16(istream &fichier);

struct Film;
struct Acteur;
struct ListeActeurs;
class ListeFilms;

Film *lireFilm(istream &fichier, ListeFilms &listeFilms);
void detruireFilm(Film *film);

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
	ListeActeurs(const ListeActeurs &liste)
	{
		capacite = liste.capacite;
		nElements = liste.nElements;
		elements = make_unique<shared_ptr<Acteur>[]>(capacite);
		for (int i = 0; i < nElements; i++)
		{
			elements[i] = liste.elements[i];
		}
	}
	ListeActeurs(unsigned int cap, int n)
	{
		capacite = cap;
		nElements = n;
		elements = make_unique<shared_ptr<Acteur>[]>(n);
	}
	friend ostream &operator<<(ostream &os, const Acteur &acteur);
	ListeActeurs operator=(const ListeActeurs &liste)
	{
		return liste;
	}

	void ajouterActeur(shared_ptr<Acteur> acteur)
	{
		if (capacite == nElements)
		{
			int nouvelleCapacite = max(1, 2 * capacite);
			unique_ptr<shared_ptr<Acteur>[]> nouvelleListe = make_unique<shared_ptr<Acteur>[]>(nouvelleCapacite);
			for (int i : range(nElements))
			{
				nouvelleListe[i] = elements[i];
			}
			elements = move(nouvelleListe);
			capacite = nouvelleCapacite;
		}
		elements[nElements] = acteur;
		nElements++;
	}
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

	friend ostream &operator<<(ostream &os, const Film &film);
};

struct Acteur
{
	std::string nom;
	int anneeNaissance;
	char sexe;
	// ListeFilms joueDans;
};



class ListeFilms
{
public:
	ListeFilms()
	{ // Constructeur par defaut
		capacite_ = 0;
		nElements_ = 0;
		elements_ = {};
	}

	ListeFilms(string nomFichier)
	{
		ListeFilms temp = creerListe(nomFichier);
		capacite_ = temp.capacite_;
		nElements_ = temp.nElements_;
		elements_ = temp.elements_;
	}


	int getnElements()
	{
		return nElements_;
	}

	Film **getElements()
	{
		return elements_;
	}

	ListeFilms creerListe(string nomFichier)
	{

		ifstream fichier(nomFichier, ios::binary);
		fichier.exceptions(ios::failbit);

		int nElements = lireUint16(fichier);

		ListeFilms listeFilms;

		for ([[maybe_unused]] int i : range(nElements))
		{
			Film *film = lireFilm(fichier, listeFilms);
			listeFilms.ajouterFilm(film);
		}
		return listeFilms;
	}

	void ajouterFilm(Film *film)
	{
		if (capacite_ == nElements_)
		{
			int nouvelleCapacite = max(1, 2 * capacite_);
			Film **nouvelleListe = new Film *[nouvelleCapacite];
			for (int i : range(nElements_))
			{
				nouvelleListe[i] = elements_[i];
			}
			delete[] elements_;
			elements_ = nouvelleListe;
			capacite_ = nouvelleCapacite;
		}
		elements_[nElements_] = film;
		nElements_++;
	}

	void enleverFilm(Film *filmAEnlever)
	{
		for (int i : range(nElements_))
		{
			if (elements_[i] == filmAEnlever)
			{
				if (i != nElements_ - 1)
				{
					elements_[i] = elements_[nElements_ - 1];
					nElements_--;
				}
				else
				{
					nElements_--;
				}
			}
		}
	}

	shared_ptr<Acteur> trouverActeur(const string &nomActeur)
	{
		for (int i : range(nElements_))
		{
			Film *film = elements_[i];
			for (shared_ptr<Acteur> &acteur : span<shared_ptr<Acteur>>(film->acteurs.elements.get(), film->acteurs.nElements))
			{
				if (acteur->nom == nomActeur)
					return acteur;
			}
		}

		return nullptr;
	}

	void detruire()
	{
		for (int i : range(nElements_))
		{
			detruireFilm(elements_[i]);
		}
		delete[] elements_;
	}

	void afficher() const
	{
		static const string ligneDeSeparation = "\n\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\n";
		cout << ligneDeSeparation;
		for (Film *film : span<Film *>(elements_, nElements_))
		{
			cout << *film;
			cout << ligneDeSeparation;
		}
	}

	Film *operator[](const int &index)
	{
		return elements_[index];
	}

	template <typename T>
	Film *afficherFilmParCritere(const T &critere)
	{
		for (int i : range(nElements_))
		{
			if (critere(elements_[i]))
			{
				return elements_[i];
			}
		}
		return nullptr;
	}

	// // void afficherFilmographieActeur(const string& nomActeur)
	// // {
	// // 	const Acteur* acteur = trouverActeur(nomActeur);
	// // 	if (acteur == nullptr)
	// // 		cout << "Aucun acteur de ce nom" << endl;
	// // 	else
	// // 		acteur->joueDans.afficher();
	// // }

private:
	int capacite_, nElements_;
	Film **elements_;
};
