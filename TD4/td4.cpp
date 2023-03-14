/*
nom: td4.cpp
description: Contient les fonctions pour lire un fichier et pour gerer un objet de type Film ainsi que les appels de fonction
auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
date: 19 mars 2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <memory>

#include <iomanip>
#include <sstream>

#include "cppitertools/range.hpp"
#include "gsl/span"

#include "structures.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"

using namespace std;
using namespace iter;
using namespace gsl;

typedef uint8_t UInt8;
typedef uint16_t UInt16;

#pragma region Fonctions de base pour lire le fichier binaire

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char *)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char *)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char *)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

#pragma endregion

shared_ptr<Acteur> lireActeur(istream& fichier, ListeFilms& listeFilms)
{
	Acteur acteur = {};
	acteur.nom = lireString(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);

	shared_ptr<Acteur> acteurExistant = listeFilms.trouverActeur(acteur.nom);
	if (acteurExistant != nullptr)
	{
		cout << "L'Acteur existe et son nom est le suivant : " << acteurExistant->nom << endl;
		return acteurExistant;
	}
	cout << "Un nouvel acteur a été créé et son nom est : " << acteur.nom << endl;
	acteurExistant = make_shared<Acteur>(Acteur(acteur));
	return acteurExistant;
}

Film* lireFilm(istream& fichier, ListeFilms& listeFilms)
{
	Film film = {};
	film.titre = lireString(fichier);
	film.realisateur = lireString(fichier);
	film.anneeSortie = lireUint16(fichier);
	film.recette = lireUint16(fichier);
	int nElements = lireUint8(fichier);

	Film *filmAlloue = new Film(film);
	for ([[maybe_unused]] int i : range(nElements))
	{
		filmAlloue->acteurs.ajouterElement(lireActeur(fichier, listeFilms));
	}
	return filmAlloue;
}

ostream& operator<<(ostream& os, const Acteur& acteur)
{
	os << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
	return os;
}

ostream& operator<<(ostream& os, const Film& film)
{
	os << "Les acteurs qui jouent dans le film " << film.titre << " sont" << endl;
	for (int i : range(film.acteurs.nElements))
	{
		os << *film.acteurs.elements[i];
	}
	return os;
}

ostream& operator<<(ostream& os, const Item& item) {
	os << item.titre << endl;
	return os;
}

vector<Item> LireLivres(const string txtLivres, vector<Item> vector)
{
	ifstream fichier(txtLivres);

	while (!fichier.eof()) {
		Livre item(fichier);
		vector.push_back(item);

	}

	fichier.close();
	return vector;
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi();

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	ListeFilms liste("films.bin");
	vector<Item> bibliotheque;
	for (int i : range(liste.getnElements())) {
		bibliotheque.push_back(*liste.getElements()[i]);
	}

	bibliotheque = LireLivres("livres.txt", bibliotheque);

	for (Item i : bibliotheque) {
		cout << i;
	}


	liste.detruire();
}