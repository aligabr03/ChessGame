/**
* Programme qui lit du clavier un nombre entier, puis détermine si ce nombre est premier ou non. 
* \file   pb6.cpp
* \author Rayane Othmani : 2126485 et Ali Gabr : 2128904
* \date   23 janvier 2023
* Créé le 18 janvier 2023
*/

#include <iostream>
#include <cmath>

using namespace std;

bool estPremier(int n)
{
    if (n <= 1)
    {
        return false;
    }
    for (int i = n - 1; i >= 1; i--)
    {
        if (n % i == 0 && i != 1)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int nombre;
    cout << "Entrer un nombre entier :" << endl;
    cin >> nombre;
    if (estPremier(nombre))
    {
        cout << "Ce nombre est premier" << endl;
    }
    else
    {
        for (int i = 2; i <= sqrt(nombre); i++)
        {
            if (nombre % i == 0)
            {
                cout << "Ce nombre n'est pas premier car il est divisble par " << i << endl;
                break;
            }
        }
    }
    return 0;
}