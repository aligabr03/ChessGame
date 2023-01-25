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

const int DICTIONARY_SIZE = 1000;  // Nombre de mots dans le dictionnaire
const string DICTIONARY_FILE = "dictionnaire.txt";  // Nom du fichier contenant le dictionnaire

struct Word {
    string word;
    string nature;
    string definition;
};

int main() {
    // Création du tableau de structures pour stocker les mots du dictionnaire
    Word dictionary[DICTIONARY_SIZE];

    // Ouverture du fichier contenant le dictionnaire
    ifstream file(DICTIONARY_FILE);

    // Lecture du dictionnaire ligne par ligne
    string line;
    int wordCount = 0;
    while (getline(file, line)) {
        // Séparation des champs de la ligne (mot, nature, définition) en utilisant le caractère de tabulation
        int tabIndex = line.find("\t");
        dictionary[wordCount].word = line.substr(0, tabIndex);
        int nextTabIndex = line.find("\t", tabIndex + 1);
        dictionary[wordCount].nature = line.substr(tabIndex + 1, nextTabIndex - tabIndex - 1);
        dictionary[wordCount].definition = line.substr(nextTabIndex + 1);
        wordCount++;
    }

    // Fermeture du fichier
    file.close();

    // Recherche du mot le plus long
    string longestWord = "";
    for (int i = 0; i < wordCount; i++) {
        if (dictionary[i].word.length() > longestWord.length()) {
            longestWord = dictionary[i].word;
        }
    }

    // Affichage du mot le plus long dans le format demandé
    for (int i = 0; i < wordCount; i++) {
        if (dictionary[i].word == longestWord) {
            cout << dictionary[i].word << " (" << dictionary[i].nature << ") : " << dictionary[i].definition << endl;
            break;
        }
    }

    return 0;
}

