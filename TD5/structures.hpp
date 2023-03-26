/*
Nom: structures.hpp
Description:
  Contient les definitions des classes et des méthodes de Film, Livre, Item, Liste et ListeFilm ainis que de la structure Acteurs.
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 18 mars 2023
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

	shared_ptr<T>* begin()
	{
		return &elements[0];
	}

	shared_ptr<T>* end()
	{
		return &elements[nElements];
	}

	const shared_ptr<T>* begin() const
	{
		return &elements[0];
	}

	const shared_ptr<T>*  end() const
	{
		return &elements[nElements];
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
	string titre = "";
	int annee = 0;

	void lireFichier(ifstream &fichier)
	{
		fichier >> quoted(titre) >> annee;
	}

	friend class ListeFilms;
	friend Film *lireFilm(istream &fichier, ListeFilms &listeFilms);
	friend ostream &operator<<(ostream &os, const Film &film);

	void afficher() const override
	{
		cout << titre;
	}
};

class Film : virtual public Item
{
public:
	string realisateur;
	int recette;
	ListeActeurs acteurs;
	Film()
	{
		realisateur = "";
		recette = 0;
	}
	Film(unsigned int capacite, int nElements, string rea, int rec)
	{
		acteurs = ListeActeurs(capacite, nElements);
		realisateur = rea;
		recette = rec;
	}

	friend class ListeFilms;
	friend Film *lireFilm(istream &fichier, ListeFilms &listeFilms);
	friend void detruireFilm(Film *film);

	void afficher() const override
	{
		Item::afficher();
		cout << ", par le réalisateur : " << realisateur << endl;
		// cout << "Acteurs : " << endl;
		// for (shared_ptr<Acteur> &acteur : span<shared_ptr<Acteur>>(this->acteurs.elements.get(), this->acteurs.nElements))
		// {
		// 	cout << *acteur;
		// }
	}
};

class Livre : virtual public Item
{
public:
	string auteur;
	int copiesVendues, nbDePages;
	Livre(ifstream &fichier)
	{
		Item::lireFichier(fichier);
		lireFichier(fichier);
	}

	void lireFichier(ifstream &fichier)
	{
		fichier >> quoted(auteur) >> copiesVendues >> nbDePages;
	}

	void afficher() const override
	{
		Item::afficher();
		cout << ", par l'auteur : " << auteur << endl;
	}

	void afficherInfo() const
	{
		cout << "Et de l'auteur : " << auteur << endl;
	}
};

class FilmLivre : public Film, public Livre
{
public:
	FilmLivre(const Film &film, const Livre &livre) : Item(film), Film(film), Livre(livre) {}

	void afficher() const override
	{
		Film::afficher();
		Livre::afficherInfo();
	}
};

struct Acteur
{
	string nom;
	int anneeNaissance;
	char sexe;
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

private:
	int capacite_, nElements_;
	Film **elements_;
};
