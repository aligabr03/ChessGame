/*
nom: td2.cpp
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

void detruireFilm(Film* film)
{
	for (int i : range(film->acteurs.nElements))
	{
		shared_ptr<Acteur> acteur = film->acteurs.elements[i];
	}
	delete film;
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

int main()
{
	bibliotheque_cours::activerCouleursAnsi(); // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	cout << ligneDeSeparation << endl;

	Liste<string> listeTextes;

	shared_ptr<string> test1 = make_shared<string>("Test1");
	shared_ptr<string> test2 = make_shared<string>("Test2");

	listeTextes.ajouterElement(test1);
	listeTextes.ajouterElement(test2);
	Liste<string> listeTextes2 = listeTextes;

	listeTextes[0] = make_shared<string>("Remplacement Test1");
	*listeTextes[1] += "Modification";

	cout << *listeTextes[0] << endl;
	cout << *listeTextes[1] << endl;
	cout << *listeTextes2[0] << endl;
	cout << *listeTextes2[1] << endl;
	cout << ligneDeSeparation << endl;
	// TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms liste("films.bin");

	Film skylien = *liste[0];
	skylien.titre = "Skylien";
	skylien.acteurs.elements[0] = liste[1]->acteurs.elements[0];
	skylien.acteurs.elements[0].get()->nom = "Daniel Wroughton Craig";
	cout << ligneDeSeparation << endl;
	cout << skylien << endl;
	cout << *liste[0] << endl;
	cout << *liste[1] << endl;
	cout << ligneDeSeparation << endl;

	Film *film = liste.afficherFilmParCritere([](const Film *film)
											  { return film->recette == 955; });
	cout << "Le premier film ayant pour recette 955 M$ est : " << film->titre << endl;

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	// TODO: Afficher le premier film de la liste. Devrait être Alien.
	cout << liste.getElements()[0]->titre << endl;
	cout << ligneDeSeparation << "Les films sont:" << endl;
	// TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	liste.afficher();
	// TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 
	//(elle était 0 dans les données lues du fichier).  
	// Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
	shared_ptr<Acteur> acteurBenedict = liste.trouverActeur("Benedict Cumberbatch");
	acteurBenedict->anneeNaissance = 1976;
	// TODO: Détruire et enlever le premier film de la liste (Alien).  
	//Ceci devrait "automatiquement" (par ce que font vos fonctions) détruire les acteurs Tom Skerritt et John Hurt, 
	//mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	detruireFilm(liste.getElements()[0]);
	liste.enleverFilm(liste.getElements()[0]);
	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	// TODO: Afficher la liste des films.
	liste.afficher();
	// TODO: Détruire tout avant de terminer le programme.  La bibliothèque de verification_allocation devrait afficher "Aucune fuite detectee."
	// a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	liste.detruire();
}