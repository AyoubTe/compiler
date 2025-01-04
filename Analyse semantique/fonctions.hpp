#ifndef FONCTIONS_HPP_INCLUDED
#define FONCTIONS_HPP_INCLUDED
enum Type { ENTIER, CARACTERE, VOID };
enum Classe { var, fonc, tab};

void programme();
void programme_prime();
void liste_declarations();
void liste_fonctions();
void declaration();
void liste_declarateurs();
void liste_declarateurs_prime(int global);
void declarateur(int global);
void declarateur_prime(int global);
void fonction();
void type();
void liste_params();
void liste_params_prime();
void param();
void liste_instructions();
void instruction();
void appel_affectation();
void iteration();
void selection();
void else_prime();
void saut();
void saut_prime();
void affectation();
void bloc();
void variable();
void variable_prime();
void liste_expressions();
void liste_expressions_prime();
Type expression();
void expression_prime(Type t);
Type terme();
void terme_prime(Type t);
Type facteur();
void condition();
void condition_prime(Type t);
void suite_condition();
void appel_variable();
void binary_rel();
void binary_comp();

#endif // FONCTIONS_HPP_INCLUDED
