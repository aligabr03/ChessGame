/**
* Programme qui permet de calculer une valeur approchée de pi par la méthode de Monte‐Carlo basée sur les probabilités.
* \file   pb6.cpp
* \author Rayane Othmani : 2126485 et Ali Gabr : 2128904
* \date   23 janvier 2023
* Créé le 22 janvier 2023
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

void genererPointAleatoire(double &x, double &y)
{
    x = (2 * (double)rand() / RAND_MAX) - 1;
    y = (2 * (double)rand() / RAND_MAX) - 1;

}

int main()
{
    srand(time(NULL));
    double x, y;
    int nbPoints;
    int nbpPointsDansCercle = 0;
    const double valeurPiEnonce = 3.141593;

    cout << "Entrez le nombre de points (d'itérations) que vous souhaitez avoir" << endl;
    cin >> nbPoints;

    for (int i = 0; i < nbPoints; i++)
    {
        genererPointAleatoire(x, y);
        if (pow(x, 2) + pow(y, 2) < 1)
        {
            nbpPointsDansCercle++;
        }
    }

    double approximationPi = 4 * (double)nbpPointsDansCercle / nbPoints;
    double ecartRelatif = abs(approximationPi - valeurPiEnonce);

    cout << "La valeur approchée de Pi par la méthode de Monte-Carlo en utilisant " << nbPoints << " Points aléatoire est : ";
    cout << fixed << setprecision(6) << approximationPi << endl;
    cout << "L'écart relatif est de :" << ecartRelatif << endl;

    return 0;
}