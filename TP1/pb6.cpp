/**
* Programme de traitement de données pour un dictionnaire (mot, nature/genre, définition).
* \file   pb6.cpp
* \author Rayane Othmani : 2126485 et Ali Gabr : 2128904
* \date   23 janvier 2023
* Créé le 23 janvier 2023
*/

#include <iostream>
#include <fstream>
using namespace std;

struct TableauDeStructure
{
    string mot;
    string natureGenre;
    string definition;
    string separateur; 
};

int main()
{
    const int NB_MAX_ENTREE = 100;
    TableauDeStructure dictionnaire[NB_MAX_ENTREE];
    ifstream fichier("dictionnaire.txt");

    // Lecture du fichier et remplissage du tableau de structures
    int entree = 0;
    while (fichier >> dictionnaire[entree].mot >> dictionnaire[entree].separateur >> dictionnaire[entree].natureGenre >> dictionnaire[entree].separateur  >> dictionnaire[entree].definition)
    {
        entree++;
    }

    // Recherche du mot le plus long
    int indexMotLong = 0;
    for (int i = 1; i < entree; i++)
    {
        if (dictionnaire[i].mot.length() > dictionnaire[indexMotLong].mot.length())
        {
            indexMotLong = i;
        }
    }

    // Affichage du mot le plus long
    cout << dictionnaire[indexMotLong].mot << " (" << dictionnaire[indexMotLong].natureGenre << ") : " << dictionnaire[indexMotLong].definition << endl;

    return 0;
}

