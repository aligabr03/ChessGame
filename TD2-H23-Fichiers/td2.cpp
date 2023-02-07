#pragma region "Includes"		//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.

#include "structures.hpp" // Structures de données pour la collection de films en mémoire.

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>

#include "cppitertools/range.hpp"
#include "gsl/span"


#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "debogage_memoire.hpp"		   // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

using namespace std;
using namespace iter;
using namespace gsl;

#pragma endregion //}

typedef uint8_t UInt8;
typedef uint16_t UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire" //{

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

#pragma endregion //}

// TODO: Une fonction pour ajouter un Film à une ListeFilms, le film existant déjà; on veut uniquement ajouter le pointeur vers le film existant.  Cette fonction doit doubler la taille du tableau alloué, avec au minimum un élément, dans le cas où la capacité est insuffisante pour ajouter l'élément.  Il faut alors allouer un nouveau tableau plus grand, copier ce qu'il y avait dans l'ancien, et éliminer l'ancien trop petit.  Cette fonction ne doit copier aucun Film ni Acteur, elle doit copier uniquement des pointeurs.
void ajouterFilmDansListeFilms(ListeFilms &listeFilms, Film *film)
{
	if (listeFilms.capacite == listeFilms.nElements)
	{
		int nouvelleCapacite = max(1, 2 * listeFilms.capacite);
		Film **nouvelleListe = new Film *[nouvelleCapacite];
		for (int i : range(listeFilms.nElements))
		{
			nouvelleListe[i] = listeFilms.elements[i];
		}
		delete[] listeFilms.elements;
		listeFilms.elements = nouvelleListe;
		listeFilms.capacite = nouvelleCapacite;
	}
	listeFilms.elements[listeFilms.nElements++] = film;
}
// TODO: Une fonction pour enlever un Film d'une ListeFilms (enlever le pointeur) sans effacer le film; la fonction prenant en paramètre un pointeur vers le film à enlever.  L'ordre des films dans la liste n'a pas à être conservé.
void enleverFilmDeListeFilms(ListeFilms &liste, Film *filmAEnlever)
{
	for (int i : range(liste.nElements))
	{
		if (liste.elements[i] == filmAEnlever)
		{
			if (i != liste.nElements - 1)
			{
				liste.elements[i] = liste.elements[liste.nElements - 1];
				//delete[] liste.elements[liste.nElements - 1];
				liste.nElements--;
			}
			else
			{
				//delete[] liste.elements[i];
				liste.nElements--;
			}
		}
	}
}
// TODO: Une fonction pour trouver un Acteur par son nom dans une ListeFilms, qui retourne un pointeur vers l'acteur, ou nullptr si l'acteur n'est pas trouvé.  Devrait utiliser span.
Acteur *trouverActeur(const ListeFilms &listeFilm, const string &nomActeur)
{
	for (int i : range(listeFilm.nElements))
	{
		Film *film = listeFilm.elements[i];
		for (Acteur* &acteur : span<Acteur *>(film->acteurs.elements, film->acteurs.nElements))
		{
			if (acteur->nom == nomActeur)
				return acteur;
		}
	}

	return nullptr;
}
// TODO: Compléter les fonctions pour lire le fichier et créer/allouer une ListeFilms.
// La ListeFilms devra être passée entre les fonctions, pour vérifier l'existence d'un Acteur
// avant de l'allouer à nouveau (cherché par nom en utilisant la fonction ci-dessus).
Acteur *lireActeur(istream &fichier, ListeFilms &listeFilms)
{
	Acteur acteur = {};
	acteur.nom = lireString(fichier);
	acteur.anneeNaissance = lireUint16(fichier);
	acteur.sexe = lireUint8(fichier);
	// TODO: Retourner un pointeur soit vers un acteur existant ou un nouvel acteur ayant les bonnes informations,
	// selon si l'acteur existait déjà.  Pour fins de débogage, affichez les noms des acteurs crées;
	// vous ne devriez pas voir le même nom d'acteur affiché deux fois pour la création.
	Acteur *acteurExistant = trouverActeur(listeFilms, acteur.nom);
	if (acteurExistant != nullptr)
	{
		cout << "L'Acteur existe et son nom est le suivant : " << acteurExistant->nom << endl;
		return acteurExistant;
	}
	cout << "Un nouvel acteur a été créé et son nom est : " << acteur.nom << endl;
	acteurExistant = new Acteur(acteur);
	acteurExistant->joueDans.elements = new Film * [1];
	acteurExistant->joueDans.nElements = 0;
	acteurExistant->joueDans.capacite = 1;
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
	// NOTE: Vous avez le droit d'allouer d'un coup le tableau pour les acteurs,
	// sans faire de réallocation comme pour ListeFilms.
	// Vous pouvez aussi copier-coller les fonctions d'allocation de ListeFilms ci-dessus dans des nouvelles fonctions
	// et faire un remplacement de Film par Acteur, pour réutiliser cette réallocation.
	Film* filmAlloue = new Film(film);
	filmAlloue->acteurs.elements = new Acteur * [filmAlloue->acteurs.nElements];
	for (int i : range(filmAlloue->acteurs.nElements))
	{
		// TODO: Placer l'acteur au bon endroit dans les acteurs du film.
		filmAlloue->acteurs.elements[i] = lireActeur(fichier, listeFilms);
		// TODO: Ajouter le film à la liste des films dans lesquels l'acteur joue.
		ajouterFilmDansListeFilms(filmAlloue->acteurs.elements[i]->joueDans, filmAlloue);
	}

	// TODO: Retourner le pointeur vers le nouveau film.
	//ajouterFilmDansListeFilms(listeFilms, filmAlloue);
	return filmAlloue;
}

ListeFilms creerListe(string nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	int nElements = lireUint16(fichier);

	// TODO: Créer une liste de films vide.
	ListeFilms listeFilms;
	listeFilms.nElements = 0;
	listeFilms.capacite = 1;
	listeFilms.elements = new Film* [nElements];
	for (int i : range(nElements))
	{
		// TODO: Ajouter le film à la liste.
		Film* film = lireFilm(fichier, listeFilms);
		ajouterFilmDansListeFilms(listeFilms, film);
	}

	// TODO: Retourner la liste de films.
	return listeFilms;
}

// TODO: Une fonction pour détruire un film (relâcher toute la mémoire associée à ce film,
// et les acteurs qui ne jouent plus dans aucun films de la collection).
// Noter qu'il faut enleve le film détruit des films dans lesquels jouent les acteurs.
// Pour fins de débogage, affichez les noms des acteurs lors de leur destruction.
void detruireFilm(Film *film)
{
	for (int i : range(film->acteurs.nElements))
	{
		Acteur *acteur = film->acteurs.elements[i];
		enleverFilmDeListeFilms(acteur->joueDans, film);
		if (acteur->joueDans.nElements == 0)
		{
			cout << " L'acteur " << acteur->nom << " va être détruit" << endl;
			delete acteur;
		}
	}
	delete[] film->acteurs.elements;
	delete film;
}

// TODO: Une fonction pour détruire une ListeFilms et tous les films qu'elle contient.
void detruireListeFilms(ListeFilms &listeFilms)
{
	for (int i : range(listeFilms.nElements))
	{
		detruireFilm(listeFilms.elements[i]);
	}
	delete[] listeFilms.elements;
}

void afficherActeur(const Acteur &acteur)
{
	cout << "  " << acteur.nom << ", " << acteur.anneeNaissance << " " << acteur.sexe << endl;
}

// TODO: Une fonction pour afficher un film avec tous ces acteurs (en utilisant la fonction afficherActeur ci-dessus).
void afficherFilm(const Film &film)
{
	cout << "Les acteurs qui jouent dans le film " << film.titre << " sont" << endl;
	for (int i : range(film.acteurs.nElements))
	{
		afficherActeur(*film.acteurs.elements[i]);
	}
}

void afficherListeFilms(const ListeFilms &listeFilms)
{
	// TODO: Utiliser des caractères Unicode pour définir la ligne de séparation (différente des autres lignes de séparations dans ce progamme).
	static const string ligneDeSeparation = "\n\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\n";
	cout << ligneDeSeparation;
	// TODO: Changer le for pour utiliser un span.
	for (Film* film : span<Film *>(listeFilms.elements, listeFilms.nElements-1))
	{
		// TODO: Afficher le film.
		afficherFilm(*film);
		cout << ligneDeSeparation;
	}
}

void afficherFilmographieActeur(const ListeFilms &listeFilms, const string &nomActeur)
{
	// TODO: Utiliser votre fonction pour trouver l'acteur (au lieu de le mettre à nullptr).
	const Acteur *acteur = trouverActeur(listeFilms, nomActeur);
	if (acteur == nullptr)
		cout << "Aucun acteur de ce nom" << endl;
	else
		afficherListeFilms(acteur->joueDans);
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi(); // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	// TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.

	// TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.  Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms listeFilms = creerListe("films.bin");

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	// TODO: Afficher le premier film de la liste.  Devrait être Alien.
	cout << listeFilms.elements[0] -> titre << endl;
	cout << ligneDeSeparation << "Les films sont:" << endl;
	// TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	afficherListeFilms(listeFilms);
	// TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).  Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
	Acteur* actriceBenedict = trouverActeur(listeFilms, "Benedict Cumberbatch");
	actriceBenedict->anneeNaissance = 1976;
	cout << ligneDeSeparation << "Liste des films où Benedict Cumberbatch joue sont:" << endl;
	// TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	afficherFilmographieActeur(listeFilms, "Benedict Cumberbatch" );
	// TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait "automatiquement" (par ce que font vos fonctions) détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	detruireFilm(listeFilms.elements[0]);
	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	// TODO: Afficher la liste des films.
	afficherListeFilms(listeFilms);
	// TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

	// TODO: Détruire tout avant de terminer le programme.  La bibliothèque de verification_allocation devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
}
