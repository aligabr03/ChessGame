/*
nom: td2.cpp
description: Contient les fonctions pour lire un fichier et pour gerer un objet de type Film ainsi que les appels de fonction
auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
date: 12 fevrier 2023
*/

#include "structures.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <memory>

#include "cppitertools/range.hpp"
#include "gsl/span"

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
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
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
	film.acteurs.nElements = lireUint8(fichier);

	Film* filmAlloue = new Film(film.acteurs.capacite, film.acteurs.nElements, film.titre, film.realisateur, film.anneeSortie, film.recette);
	for (int i : range(filmAlloue->acteurs.nElements))
	{
		filmAlloue->acteurs.elements[i] = lireActeur(fichier, listeFilms);
		// filmAlloue->acteurs.elements[i]->joueDans.ajouterFilm(filmAlloue);
	}
	return filmAlloue;
}

void detruireFilm(Film* film)
{
	for (int i : range(film->acteurs.nElements))
	{
		shared_ptr<Acteur> acteur = film->acteurs.elements[i];
		// acteur->joueDans.enleverFilm(film);
		// int nElementsJoueDans = acteur->joueDans.getnElements();
		// if ( nElementsJoueDans == 0){
		// 	cout << " L'acteur " << acteur->nom << " va être détruit" << endl;
			// delete[] acteur->joueDans.getElements();
		// delete acteur;
		}
	delete film;
}

void afficherActeur(const Acteur& acteur)
{
	cout << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
}

ostream& operator<<(ostream& os, const Film& film)
{
	os << "Les acteurs qui jouent dans le film " << film.titre << " sont" << endl;
	for (int i : range(film.acteurs.nElements))
	{
		afficherActeur(*film.acteurs.elements[i]);
	}
	return os;
}


int main()
{
	bibliotheque_cours::activerCouleursAnsi(); // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	//static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	// TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.

	// TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms liste("films.bin");

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	// TODO: Afficher le premier film de la liste. Devrait être Alien.
	cout << liste.getElements()[0]->titre << endl;
	cout << ligneDeSeparation << "Les films sont:" << endl;
	// TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	liste.afficher();
	// TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).  Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
	shared_ptr<Acteur> acteurBenedict = liste.trouverActeur("Benedict Cumberbatch");
	acteurBenedict->anneeNaissance = 1976;
	cout << ligneDeSeparation << "Liste des films où Benedict Cumberbatch joue sont:" << endl;
	// TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	// liste.afficherFilmographieActeur("Benedict Cumberbatch");
	// TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait "automatiquement" (par ce que font vos fonctions) détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	detruireFilm(liste.getElements()[0]);
	liste.enleverFilm(liste.getElements()[0]);
	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	// TODO: Afficher la liste des films.
	liste.afficher();
	// TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	// liste.afficherFilmographieActeur("Ali Gabr");
	// TODO: Détruire tout avant de terminer le programme.  La bibliothèque de verification_allocation devrait afficher "Aucune fuite detectee."
	//a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	liste.detruire();
}