/*
nom: td3.cpp
description: Contient les fonctions pour lire un fichier et pour gerer un objet de type Film ainsi que les appels de fonction
auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
date: 1 mars 2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <memory>
#include <vector>

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

UInt8 lireUint8(istream &fichier)
{
	UInt8 valeur = 0;
	fichier.read((char *)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream &fichier)
{
	UInt16 valeur = 0;
	fichier.read((char *)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream &fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char *)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

#pragma endregion

shared_ptr<Acteur> lireActeur(istream &fichier, ListeFilms &listeFilms)
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

Film *lireFilm(istream &fichier, ListeFilms &listeFilms)
{
	Film film = {};
	film.titre_ = lireString(fichier);
	film.realisateur_ = lireString(fichier);
	film.annee_ = lireUint16(fichier);
	film.recette_ = lireUint16(fichier);
	int nElements = lireUint8(fichier);

	Film *filmAlloue = new Film(film);
	for ([[maybe_unused]] int i : range(nElements))
	{
		filmAlloue->acteurs_.ajouterElement(lireActeur(fichier, listeFilms));
	}
	return filmAlloue;
}

void detruireFilm(Film *film)
{
	for (int i : range(film->acteurs_.nElements))
	{
		shared_ptr<Acteur> acteur = film->acteurs_.elements[i];
	}
	delete film;
}

ostream &operator<<(ostream &os, const Acteur &acteur)
{
	os << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
	return os;
}

ostream &operator<<(ostream &os, const Item &item)
{
	item.afficher();
	return os;
}


void LireLivres(const string nomFichier, vector<unique_ptr<Item>>& vecteur)
{
	ifstream fichier(nomFichier);
	while (!fichier.eof())
	{
		unique_ptr<Livre> livre = make_unique<Livre>(Livre(fichier));
		vecteur.push_back(move(livre));
	}

	fichier.close();
}

void afficherListeItem(vector<unique_ptr<Item>> &vecteurItem)
{
	static const string ligneDeSeparation = "\n\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\n";
	cout << ligneDeSeparation;
	for (const auto &item : vecteurItem)
	{
		cout << *item;
		cout << ligneDeSeparation;
	}
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi(); // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	// TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).

	ListeFilms liste("films.bin");
	vector<unique_ptr<Item>> bibliotheque;
	for (int i : range(liste.getnElements()))
	{
		unique_ptr<Film> film = make_unique<Film>(*liste.getElements()[i]);
		bibliotheque.push_back(move(film));
	}

	LireLivres("livres.txt", bibliotheque);
	afficherListeItem(bibliotheque);


	liste.detruire();
}