/*
nom: ListeFilms.cpp
description: Contient les corps de methodes de la classe ListeFilms
auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
date: 12 fevrier 2023
*/

#include "structures.hpp"

#include <iostream>
#include <fstream>

#include "cppitertools/range.hpp"
#include "gsl/span"

using namespace std;
using namespace iter;
using namespace gsl;

typedef uint16_t UInt16;

UInt16 lireUint16(istream &fichier);

Film* lireFilm(istream &fichier, ListeFilms &listeFilms);
void detruireFilm(Film* film);
// void afficherFilm(const Film& film);

int ListeFilms::getnElements()
{
	return nElements_;
}

Film** ListeFilms::getElements()
{
	return elements_;
}

ListeFilms ListeFilms::creerListe(string nomFichier)
{

	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	int nElements = lireUint16(fichier);

	ListeFilms listeFilms;

	for ([[maybe_unused]] int i : range(nElements))
	{
		Film* film = lireFilm(fichier, listeFilms);
		listeFilms.ajouterFilm(film);
	}
	return listeFilms;
}

void ListeFilms::ajouterFilm(Film* film)
{
	if (capacite_ == nElements_)
	{
		int nouvelleCapacite = max(1, 2 * capacite_);
		Film** nouvelleListe = new Film *[nouvelleCapacite];
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

void ListeFilms::enleverFilm(Film *filmAEnlever)
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

shared_ptr<Acteur> ListeFilms::trouverActeur(const string &nomActeur)
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

void ListeFilms::detruire()
{
	for (int i : range(nElements_))
	{
		detruireFilm(elements_[i]);
	}
	delete[] elements_;
}

void ListeFilms::afficher() const
{
	static const string ligneDeSeparation = "\n\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\n";
	cout << ligneDeSeparation;
	for (Film *film : span<Film *>(elements_, nElements_ - 1))
	{
		cout << *film;
		cout << ligneDeSeparation;
	}
}

// void ListeFilms::afficherFilmographieActeur(const string& nomActeur)
// {
// 	const Acteur* acteur = trouverActeur(nomActeur);
// 	if (acteur == nullptr)
// 		cout << "Aucun acteur de ce nom" << endl;
// 	else
// 		acteur->joueDans.afficher();
// }
