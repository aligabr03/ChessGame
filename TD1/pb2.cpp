/**
* Programme qui demande et lit du clavier une somme d’argent qui a été prêtée, le montant remboursé chaque mois, 
ainsi que le taux d’intérêt annuel , et retourne le nombre de mois nécessaires 
pour rembourser la dette ainsi que la somme des intérêts perçus par le prêteur.
* \file   pb6.cpp
* \author Rayane Othmani : 2126485 et Ali Gabr : 2128904
* \date   23 janvier 2023
* Créé le 18 janvier 2023
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

void calculerRemboursementDuPret(double montantDuPret, double tauxInteretsAnnuel, double paiementMensuel)
{
    double tauxInteretsMensuel = (tauxInteretsAnnuel / 12) / 100;
    double detteRestante, interetsPercuesParLePreteur = 0;
    int mois = 0;
    detteRestante = montantDuPret;

    while (detteRestante > 0)
    {
        mois++;
        interetsPercuesParLePreteur += detteRestante * tauxInteretsMensuel;
        detteRestante -= paiementMensuel;
        if (detteRestante < 0)
        {
            detteRestante = 0;
        }
    }

    cout << "Nombre de mois necessaires pour rembourser la dette: " << mois << endl;
    cout << "Somme des interets percus par le preteur: " << interetsPercuesParLePreteur << endl;
}

int main()
{
    double montantDuPret, paiementMensuel, tauxInteretsAnnuel, tauxInteretsMensuel;
    double detteRestante, interetsPercuesParLePreteur = 0;
    int mois = 0;

    montantDuPret = avoirEntreeValide("Entrez le montant du pret: ", 0, INFINITY);
    paiementMensuel = avoirEntreeValide("Entrez le montant rembourse chaque mois: ", 0, INFINITY);
    tauxInteretsAnnuel = avoirEntreeValide("Entrez le taux d'interet annuel (en %): ", 0, 100);

    calculerRemboursementDuPret(montantDuPret, tauxInteretsAnnuel, paiementMensuel);

    return 0;
}
