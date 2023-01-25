/**
* Programme qui détermine la hauteur atteinte par une balle en tenant compte de la hauteur initiale et du nombre de rebonds.
* \file   pb6.cpp
* \author Rayane Othmani : 2126485 et Ali Gabr : 2128904
* \date   23 janvier 2023
* Créé le 22 janvier 2023
*/

#include <iostream>
#include <cmath>
using namespace std;

double avoirEntreeValide(string message, double min, double max)
{
    double entree;
    while (true)
    {
        cout << message;
        cin >> entree;
        if (entree >= min && (max == INFINITY || entree <= max))
        {
            break;
        }
        cout << "Entree non valide. Veuillez entrer une valeur entre " << min << " et " << max << endl;
    }
    return entree;
}

void calculerHauteurRebond(double hauteurInitiale, double nbDeRebonds, double coefficientDeRebond)
{
    const double gravite = 9.81;
    int i = 0;
    double hauteur = hauteurInitiale;
    double vitesse = 0;
    double vitessePrecedente = 0;

    while (i < nbDeRebonds)
    {
        vitessePrecedente = sqrt(2 * gravite * hauteur);
        vitesse = coefficientDeRebond * vitessePrecedente;
        hauteur = pow(vitesse, 2) / (2 * gravite);
        i++;
    }

    cout << "La hauteur apres " << nbDeRebonds << " rebonds, est de : " << hauteur << " unite de hauteur. " << endl;
}

int main()
{
    double hauteurInitiale, nbDeRebonds, coefficientDeRebond;
    double gravite = 9.81;

    hauteurInitiale = avoirEntreeValide("Entrez la hauteur initiale de la balle: ", 0, INFINITY);
    nbDeRebonds = avoirEntreeValide("Entrez le nombre de rebonds au bout duquel vous souhaitez connaitre la hauteur de la balle: ", 0, INFINITY);
    coefficientDeRebond = avoirEntreeValide("Entrez la valeur du coefficient de rebond: ", 0, 1);

    calculerHauteurRebond(hauteurInitiale, nbDeRebonds, coefficientDeRebond);

    return 0;
}