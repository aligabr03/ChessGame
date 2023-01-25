/**
* Programme qui saisit un tableau d’entiers de taille 10 et qui l’affiche de telle sorte que tous les entiers pairs se retrouvent avant les entiers impairs.
* \file   pb6.cpp
* \author Rayane Othmani : 2126485 et Ali Gabr : 2128904
* \date   23 janvier 2023
* Créé le 23 janvier 2023
*/

#include <iostream>
using namespace std;
void ecrireTableau(int tableau[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        cout << "Veuillez entrez un nombre entier : " << endl;
        cin >> tableau[i];
    }
}

void afficherTableau(int tableau[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        cout << tableau[i] << " ";
    }
}

void avoirTableauTrie(int tableau[])
{
    const int TAILLE = 10;
    int tableauTrie[TAILLE];
    int compteur = 0;

    for (int i = 0; i < TAILLE; i++)
    {
        if (tableau[i] % 2 == 0)
        {
            tableauTrie[compteur] = tableau[i];
            compteur++;
        }
    }

    for (int j = 0; j < TAILLE; j++)
    {
        if (tableau[j] % 2 != 0)
        {
            tableauTrie[compteur] = tableau[j];
            compteur++;
        }
    }

    afficherTableau(tableauTrie, compteur);
}

int main()
{
    const int TAILLE = 10;
    int tableau[TAILLE];
    int tableauTrie[TAILLE];

    ecrireTableau(tableau, TAILLE);
    cout << "Le tableau initial est le suivant : " << endl;
    afficherTableau(tableau, TAILLE);

    cout << endl
         << "Le tableau trie est le suivant : " << endl;
    avoirTableauTrie(tableau);

    return 0;
}