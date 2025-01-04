#include <iostream>
#include "lexicale.cpp"
#include "semantique.cpp"

TUnite motCourant;
bool compilation = true;

int flag = 0; /// if = 1 : symbole deja inserer comme tableau
//int flagIndiceTab = 0; // verifier que la fonction comme indice d'un tableau rend un entier
int nbParams = 0; /// nombre des parametres d'une fonction
int flagTab = 0; /// si un edentificateur est un tableau ou non

Symbole* sym;
Fonction* foncourante;

vector <Symbole*> listesymboles; /// La tables des symboles
vector <Symbole*> listeParametresCourants; /// La liste des parametres
vector <Symbole*> listeVariablesLocalsCourants; /// La liste des variables locales
vector <Type> typesParametres; /// La liste des paramétres d'appel d'une fonction

string nomSymboleCourant;
string nomFonctionCourant;
string fonctionappelee;
Type typeSymboleCourant;
Type typeFonctionCourant;

void tabul(){
    for(int i=0;i<tabulation;i++){
        cout << "---|";
    }
}


bool existe(string s, vector<Symbole*> v)
{
    for (Symbole* symbole : v)
    {

        if (symbole->nom == s)
        {
            return true;
        }
    }
    return false;
}


Symbole* findSymbol(vector<Symbole*> symbols, string nom)
{
    for (Symbole* symbol : symbols)
    {
        if (symbol->nom == nom)
        {
            return symbol;
        }
    }
}

void copieTab(vector<Symbole*> t1,vector<Symbole*> t2)
{
    for (Symbole* symbol : t1)
    {
        t2.push_back(symbol);
    }
    for (Symbole* symbol : t2)
    {
        cout << symbol->nom<<endl;
    }
}

bool estTypesCorrects(vector<Symbole*> parametres, vector<Type> liste){
    for (int i = 0; i <liste.size(); i++){
        if (liste[i] != ((parametres[i])->type)) return false;
    }
    return true;
}



void programme()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "programme" << endl;

    if ( motCourant.UL == MOTCLE )
    {
        if ( strcmp(motCourant.lexeme, "int") == 0  )
        {
            typeSymboleCourant = ENTIER;
            motCourant = uniteSuivante();
            if( motCourant.UL == IDENT )
            {
                nomSymboleCourant = motCourant.lexeme;
                motCourant = uniteSuivante();
                programme_prime();
            }
            else
            {
                cout << nbLines << ") Erreur identificateur est attendu!" << endl;
                compilation = false;
                exit(0);
            }
        }
        else if (strcmp(motCourant.lexeme, "car") == 0)
        {
            typeSymboleCourant = CARACTERE;
            motCourant = uniteSuivante();
            if( motCourant.UL == IDENT )
            {
                nomSymboleCourant = motCourant.lexeme;
                motCourant = uniteSuivante();
                programme_prime();
            }
            else
            {
                cout << nbLines << ") Erreur identificateur est attendu!" << endl;
                compilation = false;
                exit(0);
            }
        }
        else if (strcmp(motCourant.lexeme, "void") == 0)
        {
            motCourant = uniteSuivante();
            if( motCourant.UL == IDENT )
            {
                nomFonctionCourant = motCourant.lexeme;
                motCourant = uniteSuivante();
                if((existe(nomFonctionCourant, listesymboles))==1)
                {
                    cout << nbLines << ") redifinition de " << nomFonctionCourant << endl;
                }
                if( motCourant.UL == PO)
                {
                    motCourant = uniteSuivante();
                    liste_params();
                    if( motCourant.UL == PF )
                    {
                        if((existe(nomSymboleCourant, listeParametresCourants))==0)
                        {
                            listeParametresCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
                        }
                        motCourant = uniteSuivante();
                        if( motCourant.UL == ACO )
                        {
                            motCourant = uniteSuivante();
                            liste_declarations();
                            Fonction* f= new Fonction(nomFonctionCourant,VOID,fonc);
                            f->parametres.assign(listeParametresCourants.begin(), listeParametresCourants.end());
                            f->variablesLocal.assign(listeVariablesLocalsCourants.begin(), listeVariablesLocalsCourants.end());
                            if((existe(nomFonctionCourant, listesymboles))==0)
                            {
                                listesymboles.push_back(f);
                            }
                            liste_instructions();
                            listeParametresCourants.clear();
                            listeVariablesLocalsCourants.clear();
                            if( motCourant.UL == ACF )
                            {
                                motCourant = uniteSuivante();
                                liste_fonctions();
                            }
                            else
                            {
                                cout << nbLines << ") Erreur } est attendu" << endl;
                                compilation = false;
                                exit(0);
                            }
                        }
                        else
                        {
                            cout << nbLines << ") Erreur { est attendu" << endl;
                            compilation = false;
                            exit(0);
                        }
                    }
                    else
                    {
                        cout << nbLines << ") Erreur ) est attendu" << endl;
                        compilation = false;
                        exit(0);
                    }
                }
                else
                {
                    cout << nbLines << ") Erreur ( est attendu!" << endl;
                    compilation = false;
                    exit(0);
                }
            }
        }
    }
    else if (strcmp(motCourant.lexeme, "fin") == 0)
    {
        cout << "" ;
    }
    else
    {
        cout << "Sythaxe erronee" << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;

}

void programme_prime()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "programme prime" << endl;
    declarateur_prime(1);
    liste_declarateurs_prime(1);
    if (motCourant.UL == PV)
    {

        if(flag==0)
        {
            if(existe(nomSymboleCourant, listesymboles)==0)
            {
                listesymboles.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
            }
            else
            {
                tabul();
                cout << nbLines << ") reddefinition de variable " << nomSymboleCourant << endl;
            }
        }

        flag = 0;
        motCourant = uniteSuivante();
        programme();
    }
    else if (motCourant.UL == PO)
    {
        nomFonctionCourant = nomSymboleCourant;
        typeFonctionCourant = typeSymboleCourant;
        if((existe(nomFonctionCourant, listesymboles))==1)
        {
            tabul();
            cout << nbLines << ") redifinition de " << nomFonctionCourant << endl;
        }
        motCourant = uniteSuivante();
        liste_params();
        if ( motCourant.UL == PF)
        {
            if((existe(nomSymboleCourant, listeParametresCourants))==0)
            {
                listeParametresCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
            }
            motCourant = uniteSuivante();
            if ( motCourant.UL == ACO)
            {
                motCourant = uniteSuivante();
                liste_declarations();
                Fonction* f= new Fonction(nomFonctionCourant,typeFonctionCourant,fonc);
                f->parametres.assign(listeParametresCourants.begin(), listeParametresCourants.end());
                f->variablesLocal.assign(listeVariablesLocalsCourants.begin(), listeVariablesLocalsCourants.end());
                if((existe(nomFonctionCourant, listesymboles))==0)
                {
                    listesymboles.push_back(f);
                }
                liste_instructions();
                listeParametresCourants.clear();
                listeVariablesLocalsCourants.clear();
                if (motCourant.UL == ACF)
                {
                    motCourant = uniteSuivante();
                    liste_fonctions();
                }
                else
                {
                    cout << nbLines << ") Erreur } est attendu!" << endl;
                    compilation = false;
                    exit(0);
                }
            }
            else
            {
                cout << nbLines << ") Erreur { est attendu!" << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur ) est attendu!" << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur [, , , ( ou ; est attendu!" << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;

}

void liste_declarations()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_declarations" << endl;
    if ( motCourant.UL == MOTCLE )
    {
        if (strcmp(motCourant.lexeme, "int") == 0 || strcmp(motCourant.lexeme, "car") == 0)
        {
            declaration();
            liste_declarations();
        }
    }
    tabulation--;
}

void liste_fonctions()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_fonctions" << endl;
    if (motCourant.UL == MOTCLE)
    {
        if (strcmp(motCourant.lexeme, "int") == 0 || strcmp(motCourant.lexeme, "car" ) || strcmp(motCourant.lexeme, "void" )  == 0)
        {
            fonction();
            liste_fonctions();
        }
    }
    tabulation--;
}

void declaration()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "declaration" << endl;
    if (motCourant.UL == MOTCLE)
    {
        if (strcmp(motCourant.lexeme, "int") == 0 )
        {
            typeSymboleCourant = ENTIER;
            motCourant = uniteSuivante();
            liste_declarateurs();
            if (motCourant.UL == PV)
            {
                if(flag==0)
                {
                    if((existe(nomSymboleCourant, listeVariablesLocalsCourants))==0 || (existe(nomSymboleCourant, listeParametresCourants))==0)
                    {
                        listeVariablesLocalsCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
                    }
                }
                flag=0;
                motCourant = uniteSuivante();
            }
            else
            {
                cout << nbLines << ") Erreur ; est attendu" << endl;
                compilation = false;
                exit(0);
            }
        }
        else if( strcmp(motCourant.lexeme, "car") == 0)
        {
            typeSymboleCourant = CARACTERE;
            motCourant = uniteSuivante();
            liste_declarateurs();
            if (motCourant.UL == PV)
            {
                if(flag==0)
                {
                    if((existe(nomSymboleCourant, listeVariablesLocalsCourants))==0 || (existe(nomSymboleCourant, listeParametresCourants))==0)
                    {
                        listeVariablesLocalsCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
                    }
                }
                flag=0;
                motCourant = uniteSuivante();
            }
            else
            {
                cout << nbLines << ") Erreur ; est attendu" << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur int ou car est attendu" << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur int, car est attendu" << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void liste_declarateurs()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_declarateurs" << endl;
    if ( motCourant.UL == IDENT )
    {
        declarateur(0);
        liste_declarateurs_prime(0);
    }
    else
    {
        cout << nbLines << ") Erreur identificateur est attendu" << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void liste_declarateurs_prime(int global)
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_declarateurs_prim" << endl;
    if (motCourant.UL == VIR)
    {

        if(global==1)
        {

            if(flag==0)
            {
                if(existe(nomSymboleCourant, listesymboles)==0)
                {
                    listesymboles.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
                }
                else
                {
                    tabul();
                    cout << nbLines << "redifinition de " << nomSymboleCourant << endl;
                }

            }

            flag=0;
        }
        else
        {

            if(flag==0)
            {
                if((existe(nomSymboleCourant, listeVariablesLocalsCourants))==0 || (existe(nomSymboleCourant, listeParametresCourants))==0)
                {
                    listeVariablesLocalsCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
                }
                else
                {
                    tabul();
                    cout << nbLines << "redifinition de " << nomSymboleCourant << endl;
                }
            }
            flag=0;
        }
        motCourant = uniteSuivante();
        declarateur(global);
        liste_declarateurs_prime(global);
    }
    tabulation--;
}

void declarateur(int global)
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "declarateur" << endl;
    if ( motCourant.UL == IDENT )
    {
        nomSymboleCourant = motCourant.lexeme;
        if((existe(nomSymboleCourant, listeVariablesLocalsCourants))==1 || (existe(nomSymboleCourant, listeParametresCourants))==1)
        {
            tabul();
            cout << nbLines << ") redifinition de " << nomSymboleCourant << endl;
        }

        motCourant = uniteSuivante();
        declarateur_prime(global);
    }
    else
    {
        cout << nbLines << ") Erreur identificateur est attendu" << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void declarateur_prime(int global)
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "declarateur_prime" << endl;
    if (motCourant.UL == CRO)
    {
        motCourant = uniteSuivante();
        if (motCourant.UL == CONST)
        {
            if(global==1)
            {
                if((existe(nomSymboleCourant, listesymboles))==0)
                {
                    listesymboles.push_back(new Tableau(nomSymboleCourant,typeSymboleCourant,tab,stoi(motCourant.lexeme)));
                    flag = 1;
                }
                else
                {
                    tabul();
                    cout << nbLines << ") redifinition de " << nomSymboleCourant << endl;
                    flag = 1;
                }
            }
            else
            {
                if((existe(nomSymboleCourant, listeVariablesLocalsCourants))==0)
                {
                    listeVariablesLocalsCourants.push_back(new Tableau(nomSymboleCourant,typeSymboleCourant,tab,stoi(motCourant.lexeme)));
                    flag = 1;
                }
                else
                {
                    tabul();
                    cout << nbLines << ") redifinition de " << nomSymboleCourant << endl;
                }
            }
            motCourant = uniteSuivante();
            if (motCourant.UL == CRF)
            {
                motCourant = uniteSuivante();
            }
            else
            {
                cout << nbLines << ") Erreur ] attendu" << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur CONST attendu" << endl;
            compilation = false;
            exit(0);
        }
    }
    tabulation--;
}

void fonction()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "fonction" << endl;
    if (motCourant.UL == MOTCLE)
    {
        if (strcmp(motCourant.lexeme, "int") == 0 || strcmp(motCourant.lexeme, "car") == 0 || strcmp(motCourant.lexeme, "void") == 0)
        {
            if((strcmp(motCourant.lexeme, "int") == 0))
                typeFonctionCourant = ENTIER;
            if((strcmp(motCourant.lexeme, "car") == 0))
                typeFonctionCourant = CARACTERE;
            if((strcmp(motCourant.lexeme, "void") == 0))
                typeFonctionCourant = VOID;
            motCourant = uniteSuivante();
            if (motCourant.UL == IDENT)
            {
                nomFonctionCourant = motCourant.lexeme;
                if((existe(nomFonctionCourant, listesymboles))==1)
                {
                    tabul();
                    cout << nbLines << ") redifinition de " << nomFonctionCourant << endl;
                }

                motCourant = uniteSuivante();
                if (motCourant.UL == PO)
                {
                    motCourant = uniteSuivante();
                    liste_params();
                    if (motCourant.UL == PF)
                    {
                        if((existe(nomSymboleCourant, listeParametresCourants))==0)
                        {
                            listeParametresCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
                        }
                        motCourant = uniteSuivante();
                        if (motCourant.UL == ACO)
                        {
                            motCourant = uniteSuivante();
                            liste_declarations();
                            Fonction* f = new Fonction(nomFonctionCourant,typeFonctionCourant,fonc);
                            //listeParametresCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
                            f->parametres.assign(listeParametresCourants.begin(), listeParametresCourants.end());
                            f->variablesLocal.assign(listeVariablesLocalsCourants.begin(), listeVariablesLocalsCourants.end());
                            if((existe(nomFonctionCourant, listesymboles))==0)
                            {
                                listesymboles.push_back(f);
                            }
                            liste_instructions();
                            listeParametresCourants.clear();
                            listeVariablesLocalsCourants.clear();
                            if (motCourant.UL == ACF)
                            {
                                motCourant = uniteSuivante();
                            }
                            else
                            {
                                cout << nbLines << ") Erreur } est attendu!" << endl;
                                compilation = false;
                                exit(0);
                            }
                        }
                        else
                        {
                            cout << nbLines << ") Erreur { est attendu!" << endl;
                            compilation = false;
                            exit(0);
                        }
                    }
                    else
                    {
                        cout << nbLines << ") Erreur ) est attendu!" << endl;
                        compilation = false;
                        exit(0);
                    }
                }
                else
                {
                    cout << nbLines << ") Erreur ( est attendu!" << endl;
                    compilation = false;
                    exit(0);
                }
            }
            else
            {
                cout << nbLines << ") Erreur identificateur est attendu!" << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur int ou char ou void est attendu!" << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur un type est attendu!" << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void type()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "type" << endl;
    if (strcmp(motCourant.lexeme, "int") == 0 || strcmp(motCourant.lexeme, "car") == 0 || strcmp(motCourant.lexeme, "void") == 0)
    {
        motCourant = uniteSuivante();
    }
    else
    {
        cout << nbLines << ") Erreur: Type attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void liste_params()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_params" << endl;
    if (strcmp(motCourant.lexeme, "int") == 0 || strcmp(motCourant.lexeme, "car") == 0)
    {
        param();
        liste_params_prime();
    }
    tabulation--;
}

void liste_params_prime()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_params_prime" << endl;
    if (motCourant.UL == VIR)
    {
        if((existe(nomSymboleCourant, listeParametresCourants))==0)
        {
            listeParametresCourants.push_back(new Variable(nomSymboleCourant,typeSymboleCourant,var));
        }
        motCourant = uniteSuivante();
        param();
        liste_params_prime();
    }
    tabulation--;
}

void param()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "param" << endl;
    if (strcmp(motCourant.lexeme, "int") == 0)
    {

        typeSymboleCourant = ENTIER;
        motCourant = uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            nomSymboleCourant = motCourant.lexeme;
            if((existe(nomSymboleCourant, listeParametresCourants))==1)
            {
                tabul();
                cout << nbLines << ") redefinition de " << nomSymboleCourant << endl;

            }

            motCourant = uniteSuivante();

        }
        else
        {
            cout << nbLines << ") Erreur: Identificateur attendu." << endl;
            compilation = false;
            exit(0);
        }
    }
    else if(strcmp(motCourant.lexeme, "car") == 0)
    {
        typeSymboleCourant = CARACTERE;
        motCourant = uniteSuivante();
        if (motCourant.UL == IDENT)
        {
            nomSymboleCourant = motCourant.lexeme;
            motCourant = uniteSuivante();
        }
        else
        {
            cout << nbLines << ") Erreur: Identificateur attendu." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur: Type (int/car) attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void liste_instructions()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_instructions" << endl;
    if(strcmp(motCourant.lexeme, "for") == 0 || strcmp(motCourant.lexeme, "while") == 0 ||
            strcmp(motCourant.lexeme, "if") == 0 || strcmp(motCourant.lexeme, "return") == 0 ||
            motCourant.UL == ACO ||motCourant.UL == IDENT)
    {
        instruction();
        liste_instructions();
    }
    tabulation--;
}

void instruction()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "instruction" << endl;
    if (strcmp(motCourant.lexeme, "for") == 0)
    {
        iteration();
    }
    else if (strcmp(motCourant.lexeme, "while") == 0)
    {
        iteration();
    }
    else if (strcmp(motCourant.lexeme, "if") == 0)
    {
        selection();
    }
    else if (strcmp(motCourant.lexeme, "return") == 0)
    {
        saut();
    }
    else if (motCourant.UL == ACO)
    {
        bloc();
    }
    else if (motCourant.UL == IDENT)
    {
        if(existe(motCourant.lexeme,listeParametresCourants)) sym=findSymbol(listeParametresCourants,motCourant.lexeme);
        else if(existe(motCourant.lexeme,listeVariablesLocalsCourants)) sym=findSymbol(listeVariablesLocalsCourants,motCourant.lexeme);
        else if(existe(motCourant.lexeme,listesymboles))
        {
            sym=findSymbol(listesymboles,motCourant.lexeme);
        }
        else
        {
            tabul();
            cout<< nbLines << ") variable non definie " << motCourant.lexeme << endl;
        }
        motCourant = uniteSuivante();
        appel_affectation();
    }
    else
    {
        cout << nbLines << ") Erreur for, while, if, return, identificateur ou {" << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void appel_affectation()
{
    Type t;
    Type type = sym->type;
    Classe classe = sym->classe;
    flagTab=0;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "appel_affectation" << endl;

    if (motCourant.UL == CRO)
    {
        if(sym->classe!=tab) cout << nbLines <<") " <<sym->nom << " n'est pas un tableau" << endl;
        motCourant = uniteSuivante();
        t = expression();
        if(t!=ENTIER) {
                tabul();
                cout << nbLines << ") l'indice doit etre un entier" <<endl;
        }
        if (motCourant.UL == CRF)
        {
            motCourant = uniteSuivante();
            if (motCourant.UL == AFF)
            {
                motCourant = uniteSuivante();
                t = expression();
                if(t!=type) {
                        tabul();
                        cout << nbLines <<") type non compatible" << endl;
                }
                if (motCourant.UL == PV)
                {
                    motCourant = uniteSuivante();
                }
                else
                {
                    cout << nbLines << ") Erreur: ; attendu." << endl;
                    compilation = false;
                    exit(0);
                }
            }
            else
            {
                cout << "Erreur: = attendu." << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur: ] attendu." << endl;
            compilation = false;
            exit(0);
        }
    }
    else if (motCourant.UL == AFF)
    {
        if(sym->classe == tab) cout << nbLines <<") " <<sym->nom << " est un tableau" << endl;
        motCourant = uniteSuivante();
        t = expression();
        if(t!=type) cout << nbLines <<") type non compatible" << endl;
        if (motCourant.UL == PV)
        {
            motCourant = uniteSuivante();
        }
        else
        {
            cout << nbLines << ") Erreur: ; attendu." << endl;
            compilation = false;
            exit(0);
        }
    }
    else if (motCourant.UL == PO)
    {
        fonctionappelee = sym->nom;
        if(sym->classe!=fonc) cout << nbLines <<") "  << sym->nom << " n'est pas une fonction" <<endl;
        foncourante = (Fonction*)findSymbol(listesymboles,sym->nom);
        motCourant = uniteSuivante();
        liste_expressions();
        if (motCourant.UL == PF)
        {
            motCourant = uniteSuivante();
            if (motCourant.UL == PV)
            {
                motCourant = uniteSuivante();
            }
            else
            {
                cout << nbLines << ") Erreur: ; attendu." << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur: ) attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur: [, = ou ( attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void iteration()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "iteration" << endl;
    if (strcmp(motCourant.lexeme, "for") == 0)
    {
        motCourant = uniteSuivante();
        if (motCourant.UL == PO)
        {
            motCourant = uniteSuivante();
            affectation();
            if (motCourant.UL == PV)
            {
                motCourant = uniteSuivante();
                condition();
                if (motCourant.UL == PV)
                {
                    motCourant = uniteSuivante();
                    affectation();
                    if (motCourant.UL == PF)
                    {
                        motCourant = uniteSuivante();
                        instruction();
                    }
                    else
                    {
                        cout << nbLines << ") Erreur: ) attendue." << endl;
                        compilation = false;
                        exit(0);
                    }
                }
                else
                {
                    cout << nbLines << ") Erreur: ; attendu." << endl;
                    compilation = false;
                    exit(0);
                }
            }
            else
            {
                cout << nbLines << ") Erreur: ; attendu." << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur: ( attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else if (strcmp(motCourant.lexeme, "while") == 0)
    {
        motCourant = uniteSuivante();
        if (motCourant.UL == PO)
        {
            motCourant = uniteSuivante();
            condition();
            if (motCourant.UL == PF)
            {
                motCourant = uniteSuivante();
                instruction();
            }
            else
            {
                cout << nbLines << ") Erreur: ) attendue." << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur: ( attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur: for ou while attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void selection()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "selection" << endl;
    if (strcmp(motCourant.lexeme, "if") == 0)
    {
        motCourant = uniteSuivante();
        if (motCourant.UL == PO)
        {
            motCourant = uniteSuivante();
            condition();
            if (motCourant.UL == PF)
            {
                motCourant = uniteSuivante();
                if (motCourant.UL == ACO)
                {
                    motCourant = uniteSuivante();
                    instruction();
                    if (motCourant.UL == ACF)
                    {
                        motCourant = uniteSuivante();
                        else_prime();
                    }
                    else
                    {
                        cout << nbLines << ") Erreur: } attendue." << endl;
                        compilation = false;
                        exit(0);
                    }
                }
                else
                {
                    cout << nbLines << ") Erreur: { attendue." << endl;
                    compilation = false;
                    exit(0);
                }
            }
            else
            {
                cout << nbLines << ") Erreur: ) attendue." << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur: ( attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur: if est attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void else_prime()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "else_prime" << endl;
    if (strcmp(motCourant.lexeme, "else") == 0)
    {
        motCourant = uniteSuivante();
        if (motCourant.UL == ACO)
        {
            motCourant = uniteSuivante();
            instruction();
            if (motCourant.UL == ACF)
            {
                motCourant = uniteSuivante();
            }
            else
            {
                cout << nbLines << ") Erreur: } attendue." << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur: { attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    tabulation--;
}

void saut()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "saut" << endl;
    if (strcmp(motCourant.lexeme, "return") == 0)
    {
        motCourant = uniteSuivante();
        saut_prime();
    }
    else
    {
        cout << nbLines << ") Erreur: return attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void saut_prime()
{
    Type t, t1;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "saut_prime" << endl;
    if (motCourant.UL== MOINS || motCourant.UL == CAR ||
            motCourant.UL == PO || motCourant.UL == IDENT || motCourant.UL == CONST)
    {
        t = expression();
        t1 = (((Fonction*)findSymbol(listesymboles,nomFonctionCourant))->type);
        if(t1!=t){
                tabul();
            cout <<nbLines << ") type de retour non compatible"<< endl;
        }
        if (motCourant.UL == PV)
        {
            motCourant = uniteSuivante();
        }
        else
        {
            cout << nbLines << ") Erreur: ; attendu." << endl;
            compilation = false;
            exit(0);
        }
    }
    else if (motCourant.UL == PV)
    {
        motCourant = uniteSuivante();
    }
    else
    {
        cout << nbLines << ") Erreur: identificateur , - , char, ( , constante ou ; est attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void affectation()
{
    Type type;
    Classe classe;
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "affectation" << endl;
    if (motCourant.UL == IDENT)
    {
        variable();
        type = sym->type;
        classe = sym->classe;
        if (motCourant.UL == AFF)
        {
            motCourant = uniteSuivante();
            t = expression();
            if(t!=type){
                    tabul();
                cout << nbLines << ") type non compatible" << endl;
            }
        }
        else
        {
            cout << nbLines << ") Erreur: = attendu." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur: identificateur attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void bloc()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "bloc" << endl;
    if (motCourant.UL == ACO)
    {
        motCourant = uniteSuivante();
        liste_instructions();
        if (motCourant.UL == ACF)
        {
            motCourant = uniteSuivante();
        }
        else
        {
            cout << nbLines << ") Erreur: } attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur: { attendue." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void variable()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "variable" << endl;
    if (motCourant.UL == IDENT)
    {
        if(existe(motCourant.lexeme,listeParametresCourants)) sym=findSymbol(listeParametresCourants,motCourant.lexeme);
        else if(existe(motCourant.lexeme,listeVariablesLocalsCourants)) sym=findSymbol(listeParametresCourants,motCourant.lexeme);
        else if(existe(motCourant.lexeme,listesymboles))
        {
            sym=findSymbol(listesymboles,motCourant.lexeme);
        }
        else{
            tabul();
            cout<< nbLines << ") variable non definie " << motCourant.lexeme << endl;
        }
        motCourant = uniteSuivante();
        variable_prime();
    }
    else
    {
        cout << nbLines << ") Erreur: Identificateur attendu." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}

void variable_prime()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "variable_prime" << endl;
    if (motCourant.UL == CRO)
    {
        if(sym->classe!=tab){
                tabul();
                cout << nbLines <<") " << sym->nom << " n'est pas un tableau" << endl;
        }
        motCourant = uniteSuivante();
        expression();
        if (motCourant.UL == CRF)
        {
            motCourant = uniteSuivante();
        }
        else
        {
            cout << nbLines << ") Erreur: ] attendu." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        if(sym->classe==tab)
        {
            cout<< nbLines <<") " << sym->nom << " est un tableau " <<endl;
        }
    }
    tabulation--;
}

void liste_expressions()
{
    Type t;
    nbParams = 0;
    typesParametres.clear();
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_expressions" << endl;
    if (motCourant.UL== MOINS || motCourant.UL == CAR || motCourant.UL == PO || motCourant.UL == IDENT || motCourant.UL == CONST)
    {
        nbParams++;
        t = expression();
        typesParametres.push_back(t);
        liste_expressions_prime();
    }

    if(nbParams!=((Fonction*)findSymbol(listesymboles,fonctionappelee))->parametres.size())
    {
        tabul();
        cout << nbLines << ") nombre de parametre n'est pas correct" <<endl;
    }else{
        if(!estTypesCorrects(((Fonction*)findSymbol(listesymboles,fonctionappelee))->parametres,typesParametres)){
                tabul();
                cout << nbLines << ") types des parametres ne sont pas corrects" <<endl;
        }
    }
    tabulation--;
}

void liste_expressions_prime()
{
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "liste_expressions_prime" << endl;
    if (motCourant.UL == VIR)
    {
        nbParams++;
        motCourant = uniteSuivante();
        t = expression();
        typesParametres.push_back(t);
        liste_expressions_prime();
    }
    tabulation--;
}

Type expression()
{
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "expression" << endl;
    if (motCourant.UL == CAR || motCourant.UL == PO || motCourant.UL == IDENT || motCourant.UL == CONST)
    {
        t = terme();
        expression_prime(t);
    }
    else if (motCourant.UL == MOINS)
    {
        motCourant = uniteSuivante();
        t = expression();
    }
    else
    {
        cout << nbLines << ") char , ( , constante , identificateur ou - est attendu " << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
    return t;
}

void expression_prime(Type he)
{
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "expression_prime " << "  " <<endl;
    if (motCourant.UL == PLUS || motCourant.UL == MOINS)
    {
        motCourant = uniteSuivante();
        t = terme();
        if(he!=t){
                tabul();
                cout << nbLines << ") type non compatible" <<endl;
        }
        expression_prime(he);
    }
    tabulation--;
}

Type terme()
{
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "terme" << endl;
    if (motCourant.UL == CAR || motCourant.UL == PO || motCourant.UL == IDENT || motCourant.UL == CONST)
    {
        t = facteur();
        terme_prime(t);
    }
    else
    {
        cout << nbLines << ") char , ( , constante ou identificateur est attendu  "<<endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
    return t;
}

void terme_prime(Type he)
{
    Type t,t1;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "terme_prime" << endl;
    if (motCourant.UL == MULT || motCourant.UL == DIV)
    {
        motCourant = uniteSuivante();
        t = facteur();
        if(he!=t){
                tabul();
                cout << nbLines << ") type non compatible" <<endl;
        }
        terme_prime(he);
    }
    tabulation--;
}

Type facteur()
{
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "facteur" << endl;
    if (motCourant.UL == IDENT)
    {
        if(existe(motCourant.lexeme,listeParametresCourants)) sym=findSymbol(listeParametresCourants,motCourant.lexeme);
        else if(existe(motCourant.lexeme,listeVariablesLocalsCourants)) sym=findSymbol(listeVariablesLocalsCourants,motCourant.lexeme);
        else if(existe(motCourant.lexeme,listesymboles))
        {
            sym=findSymbol(listesymboles,motCourant.lexeme);
        }
        else
        {
            tabul();
            cout<< nbLines << ") variable non definie " << motCourant.lexeme << endl;
        }
        t = sym->type;
        motCourant = uniteSuivante();
        appel_variable();
    }
    else if (motCourant.UL == CONST)
    {
        t = ENTIER;
        motCourant = uniteSuivante();
    }
    else if(motCourant.UL == CAR)
    {
        t = CARACTERE;
        motCourant = uniteSuivante();
    }
    else if (motCourant.UL == PO)
    {
        motCourant = uniteSuivante();
        t = expression();
        if (motCourant.UL == PF)
        {
            motCourant = uniteSuivante();
        }
        else
        {
            cout << nbLines << ") Erreur: ) attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else
    {
        cout << nbLines << ") Erreur: Facteur mal formé." << endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
    return t;
}

void condition()
{
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "condition" << endl;
    if (motCourant.UL == NOT)
    {
        motCourant = uniteSuivante();
        if (motCourant.UL == PO)
        {
            motCourant = uniteSuivante();
            condition();
            if (motCourant.UL == PF)
            {
                motCourant = uniteSuivante();
                suite_condition();
            }
            else
            {
                cout << nbLines << ") Erreur: ) attendue." << endl;
                compilation = false;
                exit(0);
            }
        }
        else
        {
            cout << nbLines << ") Erreur: ( attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else if(motCourant.UL == CONST || motCourant.UL == CAR || motCourant.UL == MOINS || motCourant.UL == IDENT || motCourant.UL == PO)
    {
        t= expression();
        condition_prime(t);
    }
    else
    {
        cout << nbLines << ") Erreur ! , char , constante , ( ou identificateur est attendu"<<endl;
        compilation = false;
        exit(0);
    }
    tabulation--;
}


void condition_prime(Type he)
{
    Type t;
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "condition_prime" << endl;
    if (motCourant.UL == INF || motCourant.UL == SUP || motCourant.UL == EGAL
            || motCourant.UL == INFEG || motCourant.UL == SUPEG || motCourant.UL == DIFF)
    {
        binary_comp();
        t = expression();
        if(t!=he){
                tabul();
            cout<< nbLines <<") type non compatible" << endl;
        }
        suite_condition();
    }
    tabulation--;
}

void suite_condition()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "suite_condition" << endl;
    if (motCourant.UL == ET || motCourant.UL == OU )
    {
        binary_rel();
        condition();
    }
    tabulation--;
}

void appel_variable()
{
    tabulation++;
    for(int i=0; i<tabulation; i++)
    {
        cout << "   |";
    }
    cout << "appel_variable" << endl;
    if (motCourant.UL == PO)
    {
        fonctionappelee = sym->nom;
        if(sym->classe!=fonc)
        {
            tabul();
            cout << nbLines << ") "<< sym->nom << " n'est pas une fonction" << endl;
        }


        foncourante = (Fonction*)findSymbol(listesymboles,sym->nom);
        motCourant = uniteSuivante();
        liste_expressions();
        if (motCourant.UL == PF)
        {

            motCourant = uniteSuivante();
        }
        else
        {
            cout << nbLines << ") Erreur: ) attendue." << endl;
            compilation = false;
            exit(0);
        }
    }
    else if (motCourant.UL == CRO)
    {
        variable_prime();
    }
    else if(sym->classe == tab){
            tabul();
            cout << nbLines << ") " << sym->nom << " est un tableau" << endl;
    }
    tabulation--;
}

void binary_rel()
{
    if (motCourant.UL == ET || motCourant.UL == OU)
    {
        motCourant = uniteSuivante();
    }
    else
    {
        cout << nbLines << ") Erreur: Opérateur logique (&& ou ||) attendu." << endl;
        compilation = false;
        exit(0);
    }
}

void binary_comp()
{
    if (motCourant.UL == INF || motCourant.UL == SUP || motCourant.UL == INFEG || motCourant.UL == SUPEG || motCourant.UL == EGAL || motCourant.UL == DIFF)
    {
        motCourant = uniteSuivante();
    }
    else
    {
        cout << nbLines << ") Erreur: Opérateur de comparaison attendu." << endl;
        compilation = false;
        exit(0);
    }
}
