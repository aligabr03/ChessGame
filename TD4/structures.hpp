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
#include <iomanip>
#include <sstream>

using namespace iter;
using namespace std;
using namespace gsl;

typedef uint16_t UInt16;

UInt16 lireUint16(istream &fichier);

class Film;
class Livre;
struct Acteur;
class ListeFilms;

Film *lireFilm(istream &fichier, ListeFilms &listeFilms);
void detruireFilm(Film *film);
ostream &operator<<(ostream &os, const Acteur &acteur);

template <typename T>
class Liste
{
public:
	int capacite, nElements;
	unique_ptr<shared_ptr<T>[]> elements;
	Liste()
	{
		capacite = 0;
		nElements = 0;
		elements = make_unique<shared_ptr<T>[]>(0);
	}
	Liste(const Liste &liste)
	{
		capacite = liste.capacite;
		nElements = liste.nElements;
		elements = make_unique<shared_ptr<T>[]>(capacite);
		for (int i = 0; i < nElements; i++)
		{
			elements[i] = liste.elements[i];
		}
	}
	Liste(unsigned int cap, int n)
	{
		capacite = cap;
		nElements = n;
		elements = make_unique<shared_ptr<T>[]>(n);
	}
	friend ostream &operator<<(ostream &os, const T &elementaAfficher);
	Liste<T> operator=(const Liste<T> &liste)
	{
		return liste;
	}

	void ajouterElement(shared_ptr<T> elementaAjouter)
	{
		if (capacite == nElements)
		{
			int nouvelleCapacite = max(1, 2 * capacite);
			unique_ptr<shared_ptr<T>[]> nouvelleListe = make_unique<shared_ptr<T>[]>(nouvelleCapacite);
			for (int i : range(nElements))
			{
				nouvelleListe[i] = elements[i];
			}
			elements = move(nouvelleListe);
			capacite = nouvelleCapacite;
		}
		elements[nElements] = elementaAjouter;
		nElements++;
	}

	shared_ptr<T> &operator[](const int &index)
	{
		return elements[index];
	}
};

using ListeActeurs = Liste<Acteur>;

class Affichable
{
public:
	virtual void afficher() const = 0;
	virtual ~Affichable() {}
};

class Item : public Affichable
{
public:
	Item() {}

	void lireFichier(ifstream &fichier)
	{
		fichier >> quoted(titre_) >> annee_;
	}

	friend class ListeFilms;
	friend Film *lireFilm(istream &fichier, ListeFilms &listeFilms);
	friend ostream &operator<<(ostream &os, const Film &film);
	friend vector<Item *> LireLivres(const string txtLivres, vector<Item *> vecteur);
	void afficher() const override
	{
		cout << "Titre : " << titre_ << "\tAnnée: " << annee_ << endl;
	}

private:
	string titre_ = "";
	int annee_ = 0;
};

class Film : public Item
{
public:
	Film()
	{
		realisateur_ = "";
		recette_ = 0;
	}
	Film(unsigned int capacite, int nElements, string rea, int rec)
	{
		acteurs_ = ListeActeurs(capacite, nElements);
		realisateur_ = rea;
		recette_ = rec;
	}

	friend class ListeFilms;
	friend ostream &operator<<(ostream &os, const Film &film);
	friend Film *lireFilm(istream &fichier, ListeFilms &listeFilms);
	friend shared_ptr<Acteur> trouverActeur(const string &nomActeur);
	friend void detruireFilm(Film *film);

	void afficher() const override
	{
		Item::afficher();
		cout << "Combo :\n"
			 << "  Réalisateur : " << realisateur_ << "\n  Recette : " << recette_ << endl;
		cout << "Acteurs : " << endl;
		for (shared_ptr<Acteur> &acteur : span<shared_ptr<Acteur>>(this->acteurs_.elements.get(), this->acteurs_.nElements))
		{
			cout << *acteur;
		}
	}
	friend ostream &operator<<(ostream &os, const Film &film);

private:
	string realisateur_;
	int recette_;
	ListeActeurs acteurs_;
};

class Livre : public Item
{
public:
	Livre() {}

	Livre(ifstream &fichier)
	{
		Item::lireFichier(fichier);
		lireFichier(fichier);
	}

	void lireFichier(ifstream &fichier)
	{
		fichier >> quoted(auteur_) >> copiesVendues_ >> nbDePages_;
	}

	void afficher() const override
	{
		Item::afficher();
		cout << "Auteur : " << auteur_ << "\nCopies Vendues : " << copiesVendues_ << "M"
			 << " Pages : " << nbDePages_ << endl;
	}

	friend vector<Item *> LireLivres(const string txtLivres, vector<Item *> vecteur);

private:
	string auteur_;
	int copiesVendues_, nbDePages_;
};

// class FilmLivre : public Livre, public Film
// {
// public:
// 	FilmLivre(Film film, Livre livre)
// 	{
// 		titre_ = film.getTitre();
// 		anneeSortie_ = film.getAnnee();
// 	}

// private:
// 	string titre_ = "", realisateur_ = "", auteur_ = "";
// 	int anneeSortie_ = 0, recette_ = 0, copiesVendues_ = 0, nbDePages_ = 0;
// 	ListeActeurs acteurs_;
// };

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
			for (shared_ptr<Acteur> &acteur : span<shared_ptr<Acteur>>(film->acteurs_.elements.get(), film->acteurs_.nElements))
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

private:
	int capacite_, nElements_;
	Film **elements_;
};
