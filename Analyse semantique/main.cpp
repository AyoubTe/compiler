#include <iostream>
#include "syntaxique.cpp"

using namespace std;


int main()
{

    mot_cles();
    if (!file.is_open())
    {
        cerr << "Erreur en ouverture du fichier" << endl;
        return 1;
    }

    carCourant = lireCar();
    motCourant = uniteSuivante();
    programme();


    if(compilation){
        cout << "Votre code est correct synthaxiquement" << endl;
    }


    file.close();
    return 0;
}
