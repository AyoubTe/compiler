#include <iostream>
#include <vector>
#include "fonctions.hpp"


class Symbole {
public:
    string nom;
    Classe classe;
    Type type;
    Symbole(string n, Type t, Classe c) : nom(n), type(t), classe(c) {}
    Symbole(){}
};

class Variable:public Symbole {
public:
    Variable(string n, Type t, Classe c):Symbole(n,t,c){
    }
};

class Fonction:public Symbole {
public:
    vector <Symbole*> variablesLocal;
    vector <Symbole*> parametres;
    Fonction(string n, Type t, Classe c):Symbole(n,t,c){
    }
    Fonction(){}
};

class Tableau:public Symbole {
public:
    int taille;
    Tableau(string n, Type t, Classe c, int ta):Symbole(n,t,c), taille(ta){
    }
};
