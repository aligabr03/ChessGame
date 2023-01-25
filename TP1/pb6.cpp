/**
 * Programme de traitement de données pour un dictionnaire (mot, nature/genre, définition).
 * \file   pb6.cpp
 * \author Rayane Othmani : 2126485 et Ali Gabr : 2128904
 * \date   23 janvier 2023
 * Créé le 23 janvier 2023
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int NB_MOTS_MAX = 1000;
const string FICHIER_DICTIONNAIRE = "dictionnaire.txt";

struct EntreeDict
{
    string mot;
    string natureGenre;
    string definition;
};

int separerChampDictionnaire(const string FICHIER_DICTIONNAIRE, EntreeDict dictionnaire[])
{
    ifstream fichier(FICHIER_DICTIONNAIRE);
    string ligne;
    int compteurDeMot = 0;
    while (getline(fichier, ligne))
    {
        int indexTab = ligne.find("\t");
        dictionnaire[compteurDeMot].mot = ligne.substr(0, indexTab);
        int prochainIndexTab = ligne.find("\t", indexTab + 1);
        dictionnaire[compteurDeMot].natureGenre = ligne.substr(indexTab + 1, prochainIndexTab - indexTab - 1);
        dictionnaire[compteurDeMot].definition = ligne.substr(prochainIndexTab + 1);
        compteurDeMot++;
    }
    fichier.close();
    return compteurDeMot;
}

string trouverMotPlusLong(EntreeDict dictionnaire[], int compteurDeMot)
{
    string motPlusLong = "";
    for (int i = 0; i < compteurDeMot; i++)
    {
        if (dictionnaire[i].mot.length() > motPlusLong.length())
        {
            motPlusLong = dictionnaire[i].mot;
        }
    }
    return motPlusLong;
}

int main()
{

    EntreeDict dictionnaire[NB_MOTS_MAX];

    int compteurDeMot = separerChampDictionnaire(FICHIER_DICTIONNAIRE, dictionnaire);
    string motPlusLong = trouverMotPlusLong(dictionnaire, compteurDeMot);

    for (int i = 0; i < compteurDeMot; i++)
    {
        if (dictionnaire[i].mot == motPlusLong)
        {
            cout << dictionnaire[i].mot << " (" << dictionnaire[i].natureGenre << ") : " << dictionnaire[i].definition << endl;
            break;
        }
    }
    return 0;
}

