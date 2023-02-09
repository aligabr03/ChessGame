#include "structures.hpp" 

#include <iostream>
#include <fstream>

#include "cppitertools/range.hpp"
#include "gsl/span"

using namespace std;
using namespace iter;
using namespace gsl;

typedef uint8_t UInt8;
typedef uint16_t UInt16;

UInt16 lireUint16(istream& fichier);

struct Film; struct Acteur;

Film* lireFilm(istream& fichier, ListeFilms& listeFilms);
void detruireFilm(Film* film);
void afficherFilm(const Film& film);


ListeFilms ListeFilms::creerListe(string nomFichier) {

	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	int nElements = lireUint16(fichier);

	ListeFilms listeFilms;

	for (int i : range(nElements))
	{
		Film* film = lireFilm(fichier, listeFilms);
		listeFilms.ajouterFilm(film);
	}
	return listeFilms;
}

void ListeFilms::ajouterFilm(Film* film)
{
	if (capacite == nElements)
	{
		int nouvelleCapacite = max(1, 2 * capacite);
		Film** nouvelleListe = new Film * [nouvelleCapacite];
		for (int i : range(nElements))
		{
			nouvelleListe[i] = elements[i];
		}
		delete[] elements;
		elements = nouvelleListe;
		capacite = nouvelleCapacite;
	}
	elements[nElements] = film;
	nElements++;
}

void ListeFilms::enleverFilm(Film* filmAEnlever)
{
	for (int i : range(nElements))
	{
		if (elements[i] == filmAEnlever)
		{
			if (i != nElements - 1)
			{
				elements[i] = elements[nElements - 1];
				nElements--;
			}
			else
			{
				nElements--;
			}
		}
	}
}

Acteur* ListeFilms::trouverActeur(const string& nomActeur)
{
	for (int i : range(nElements))
	{
		Film* film = elements[i];
		for (Acteur*& acteur : span<Acteur*>(film->acteurs.elements, film->acteurs.nElements))
		{
			if (acteur->nom == nomActeur)
				return acteur;
		}
	}

	return nullptr;
}


void ListeFilms::detruire()
{
	for (int i : range(nElements))
	{
		detruireFilm(elements[i]);
	}
	delete[] elements;
}

void ListeFilms::afficher() const
{
	static const string ligneDeSeparation = "\n\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\n";
	cout << ligneDeSeparation;
	for (Film* film : span<Film*>(elements, nElements - 1))
	{

		afficherFilm(*film);
		cout << ligneDeSeparation;
	}
}

void ListeFilms::afficherFilmographieActeur(const string& nomActeur)
{
	const Acteur* acteur = trouverActeur(nomActeur);
	if (acteur == nullptr)
		cout << "Aucun acteur de ce nom" << endl;
	else
		acteur->joueDans.afficher();
}
