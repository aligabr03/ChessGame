/*
Nom: td5.cpp
Description: Programme contenant des définitions pour les méthodes de lecture du fichier binaire ainsi que des surcharges d'opérateurs
et des fonctions de Lectures. De plus, on y répond a toutes les questions concernant les listes liées
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
	film.titre = lireString(fichier);
	film.realisateur = lireString(fichier);
	film.annee = lireUint16(fichier);
	film.recette = lireUint16(fichier);
	int nElements = lireUint8(fichier);

	Film *filmAlloue = new Film(film);
	for ([[maybe_unused]] int i : range(nElements))
	{
		filmAlloue->acteurs.ajouterElement(lireActeur(fichier, listeFilms));
	}
	return filmAlloue;
}

void detruireFilm(Film *film)
{
	for (int i : range(film->acteurs.nElements))
	{
		shared_ptr<Acteur> acteur = film->acteurs.elements[i];
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

void LireLivres(const string nomFichier, vector<unique_ptr<Item>> &vecteur)
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
void afficherListeItem(C &conteneur)
{
	static const string ligneDeSeparation = "\n\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\u007C\n";
	cout << ligneDeSeparation;
	for (const auto &item : conteneur)
	{
		item->afficher();
		cout << ligneDeSeparation;
	}
}

int main()
{
	bibliotheque_cours::activerCouleursAnsi();
	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

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

	cout << ligneDeSeparation << "Affichage de la bibliothèque d'Items" << endl;
	afficherListeItem(bibliotheque);

// 1
	//  1.1
	forward_list<Item *> listeLiee;
	for (int i = size(bibliotheque) - 1; i >= 0; --i)
	{
		listeLiee.push_front(bibliotheque[i].get());
	}

	cout << ligneDeSeparation << " La liste demandée en 1.1 est la suivante" << endl;
	afficherListeItem(listeLiee);

	// 1.2
	forward_list<Item *> listeLieeInverse;
	for (auto pointeurs : listeLiee)
	{
		listeLieeInverse.push_front(pointeurs);
	}

	cout << ligneDeSeparation << " La liste demandée en 1.2 est la suivante" << endl;
	afficherListeItem(listeLieeInverse);

	// 1.3
	forward_list<Item *> listeLieeDeux;
	auto iterateurPrecedent = listeLieeDeux.before_begin();
	for (auto pointeurs : listeLiee)
	{
		iterateurPrecedent = listeLieeDeux.insert_after(iterateurPrecedent, pointeurs);
	}

	cout << ligneDeSeparation << " La liste demandée en 1.3 est la suivante" << endl;
	afficherListeItem(listeLieeDeux);

	// 1.4

	int nbElementListe = 0;
	for (auto pointeurs : listeLiee) // On parcours la liste triee en O(n)
	{
		nbElementListe++;
	}

	vector<Item *> bibliotheque2(nbElementListe);
	int index = nbElementListe;
	for (auto pointeurs : listeLiee) // On reparcours la liste triee en O(n) mais O(n) + O(n) = O(n)
	{
		bibliotheque2[index - 1] = pointeurs;
		index--;
	}

	cout << ligneDeSeparation << " La liste demandée en 1.4 est la suivante" << endl;
	afficherListeItem(bibliotheque2);

	// 1.5
	cout << ligneDeSeparation << "Les acteurs du premier film (Alien) sont :" << endl;

	Film premierFilm = *liste[0];
	for (auto &&acteur : premierFilm.acteurs)
	{
		cout << *acteur << endl;
	}

// 2
	// 2.1
	set<Item *, decltype([](Item *p1, Item *p2)
						 { return p1->titre < p2->titre; })>
		listeTriee;
	for (auto i : listeLiee)
	{
		listeTriee.insert(i);
	}
	cout << ligneDeSeparation << " La liste triée en ordre alphabétique demandée en 2.1 est la suivante" << endl;
	afficherListeItem(listeTriee);

	// 2.2

	unordered_map<string, Item *> mapTitreItem;
	for (auto &item : bibliotheque)
	{
		mapTitreItem[item->titre] = item.get();
	}

	auto iterateur = mapTitreItem.find("The Hobbit");
	if (iterateur != mapTitreItem.end())
	{
		cout << ligneDeSeparation << endl;
		cout << "Item trouve : " << endl;
		(*iterateur->second).afficher();
	}
	else
	{
		cout << ligneDeSeparation << endl;
		cout << "Item non trouve." << endl;
	}

// 3
	// 3.1
	vector<Item *> vecteurFilms;
	copy_if(listeLiee.begin(), listeLiee.end(), back_inserter(vecteurFilms), [](Item *item)
			{ return dynamic_cast<Film *>(item) != nullptr; });
	cout << ligneDeSeparation << "La liste demandée en 3.1 est :" << endl;
	afficherListeItem(vecteurFilms);

	// 3.2
	int recetteTotale = reduce(vecteurFilms.begin(), vecteurFilms.end(), 0, [](int sum, Item *film1)
							   { return sum + dynamic_cast<Film *>(film1)->recette; });
	cout << ligneDeSeparation << endl;
	cout << "La recette Totale de tous les films est de :" << recetteTotale << "M$" << endl;

	liste.detruire();
}