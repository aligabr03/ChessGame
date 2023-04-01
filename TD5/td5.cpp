/*
Nom: td4.cpp
Description: Programme contenant des définitions pour les méthodes de lecture du fichier binaire ainsi que des surcharges d'opérateurs
et des fonctions de Lectures. De plus, on y fait des appels de fonctions afin de créer une liste de Film et créer et afficher
un vecteur contenant des films et des livres auquel on y ajoute un FilmLivre.
Auteurs: Rayane Othmani (2126485) et Ali Gabr (2128904)
Date: 18 mars 2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <memory>
#include <vector>
#include <forward_list>
#include <set>
#include <map>
#include <numeric>

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
	film.annee = lireUint16(fichier);
	film.recette = lireUint16(fichier);
	int nElements = lireUint8(fichier);

	Film* filmAlloue = new Film(film);
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

ostream& operator<<(ostream& os, const Item& item)
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

template <typename C>
void afficherListeItem(C& conteneur)
{
	static const string ligneDeSeparation = "\n\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\n";
	cout << ligneDeSeparation;
	for (const auto &item : conteneur )
	{
		item->afficher();
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

	unique_ptr<FilmLivre> filmLivreLeHobbit = make_unique<FilmLivre>(dynamic_cast<Film &>(*bibliotheque[4]), dynamic_cast<Livre &>(*bibliotheque[9]));
	bibliotheque.push_back(move(filmLivreLeHobbit));


	//1.1
	forward_list<Item*> forwardList;

	for (int i = size(bibliotheque) - 1; i >= 0; --i) {
		forwardList.push_front(bibliotheque[i].get());
	}


	//1.2
	forward_list<Item*> forwardListDeux;

	for (auto i : forwardList) {
		forwardListDeux.push_front(i);
	}

	//1.3
	forward_list<Item*> forwardListTrois;
	int j = 0;
	for (auto i : forwardList) {
		forwardListTrois.insert_after(forwardListTrois.before_begin(), i);
		j++;
	}


	//1.4 Optimiser l'ordre O(..)
	//vector<Item*> vectorUnPointTrois;
	//for (auto i : forwardList) {
	//	vectorUnPointTrois.push_back(i);
	//}
	//afficherListeItem(forwardListTrois);
	//1.5
	//for (auto acteur : (*liste.elements_[1]).acteurs)

	//2.1
	set < Item*, decltype([](Item* p1, Item* p2) { return p1->titre < p2->titre; }) > listeTriee;
	for (auto i : forwardList) {
		listeTriee.insert(i);
	}


	vector<Item*> test;
	copy_if(listeTriee.begin(), listeTriee.end(), back_inserter(test), [](Item* item) {return dynamic_cast<Film*>(item) != nullptr; });


	int recetteTotale = accumulate(test.begin(), test.end(), 0, [](int sum, Item* film) {return sum + dynamic_cast<Film*>(film)->recette;});

	cout << recetteTotale;
	liste.detruire();
}