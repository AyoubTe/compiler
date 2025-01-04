#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

/// ouvrir le fichier dont le code source correct

ifstream file("code.txt");

/// ouvrir le fichier source erronee

//ifstream file("code_erronnee.txt");

/// Le caractère courant
char carCourant;

int nbLines = 1;
int tabulation = -1;

bool estBlanc(char c)
{
    return c == ' ' || c == '\t' || c== '\n';
}

bool estLettre(char c)
{
    return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}

bool estCar(char c)
{
    return 0 <= c && c <= 255;
}

bool estChiffre(char c)
{
    return '0' <= c && c <= '9';
}

char lireCar()
{
    return file.get();
}

enum UniteLexical { CAR, ERROR, PV,VIR, CRO, CRF,ACO,ACF, PO,PF,
                    MOINS,NOT, PLUS, MULT, DIV,INF,SUP, SUPEG,INFEG,
                    AFF,IDENT,CONST, ET, OU, EGAL, DIFF, MOTCLE
                  };

typedef struct
{
    UniteLexical UL;
    char *lexeme;
} TUnite;

int hashage(const string& word) {
    int hash_value = 0;
    const int prime = 31;

    for (char c : word) {
        hash_value = (hash_value * prime) + static_cast<int>(c);
    }

    hash_value = hash_value % 100;

    if (hash_value > 50) {
        hash_value -= 50;
    }

    return hash_value;
}

vector<string> motCles = {"int", "car", "then", "return", "void", "ecrire",
                            "else", "for", "while", "if", "lire"};

vector<string> hashed_table(100, "null");

void mot_cles(){
    for (const auto& mot : motCles) {
        int hash_value = hashage(mot);
        hashed_table[hash_value] = mot;
    }
}

bool estMotCle(string mot)
{
    int h = hashage(mot);
    if(hashed_table[h] == mot)
        return true;
    return false;
}


TUnite uniteSuivante()
{
    TUnite u;

    while(estBlanc(carCourant)){
        if(carCourant == '\n'){
            nbLines++;

        }
        carCourant = lireCar();
    }


    if (carCourant == EOF) {
        u.lexeme = "fin";
        return u;
    }

    switch(carCourant)
    {
    case '[':
    {
        carCourant = lireCar();
        u.lexeme = "[";
        u.UL = CRO; /// Crochee ouvrante
        return u;
    }

    case ']':
    {
        carCourant = lireCar();
        u.lexeme = "]";
        u.UL = CRF; /// Crochee Fermante
        return u;
    }

    case '{':
    {
        carCourant = lireCar();
        u.lexeme = "{";
        u.UL = ACO; /// Accolade ouvrante
        return u;
    }

    case '}':
    {
        carCourant = lireCar();
        u.lexeme = "}";
        u.UL = ACF; /// Accolade fermante
        return u;
    }

    case '(':
    {
        carCourant = lireCar();
        u.lexeme = "(";
        u.UL = PO; /// Parenthese fermante
        return u;
    }

    case ')':
    {
        carCourant = lireCar();
        u.lexeme = ")";
        u.UL = PF; /// Parenthese Fermante
        return u;
    }

    case ';':
    {
        carCourant = lireCar();
        u.lexeme = ";";
        u.UL = PV; /// Point virgule
        return u;
    }

    case ',':
    {
        carCourant = lireCar();
        u.lexeme = ",";
        u.UL = VIR; /// Virgule
        return u;
    }

    case '/':
    {
        carCourant = lireCar();
        if ( carCourant == '*' )
        {
            while( true )
            {
                carCourant = lireCar();
                if(carCourant == '*')
                {
                    carCourant = lireCar();
                    if(carCourant == '/')
                    {
                        carCourant = lireCar();
                        return uniteSuivante();
                    }
                }
            }
        }

        else
        {
            u.lexeme = "/";
            u.UL = DIV; /// Division
            return u;
        }
    }

    case '*':
    {
        carCourant = lireCar();
        if ( carCourant == '/' )
        {
            carCourant = lireCar();
            u.lexeme = "fin commentaire sans début";
            u.UL = ERROR; /// Erreur fin de commentaire sans debut
            return u;
        }
        u.lexeme ="*";
        u.UL = MULT; /// Multiplication
        return u;
    }

    case '+':
    {
        carCourant = lireCar();
        u.lexeme = "+";
        u.UL = PLUS;  /// Plus
        return u;
    }

    case '-':
    {
        carCourant = lireCar();
        u.lexeme = "-";
        u.UL = MOINS; /// Moins
        return u;
    }

    case '=':
    {
        carCourant = lireCar();
        if(carCourant == '=')
        {
            carCourant = lireCar();
            u.lexeme = "=="; /// Egal
            u.UL = EGAL;
            return u;
        }
        else
        {
            u.lexeme = "=";
            u.UL = AFF;  /// Affectation
            return u;
        }
    }
    case '<':
    {
        carCourant = lireCar();
        if(carCourant == '=')
        {
            carCourant = lireCar();
            u.lexeme = "<=";
            u.UL = INFEG;  /// Inferieur ou egal
            return u;
        }
        else
        {
            u.lexeme = "<";
            u.UL = INF;  /// Inferieur
            return u;
        }
    }
    case '>':
    {
        carCourant = lireCar();
        if(carCourant == '=')
        {
            carCourant = lireCar();
            u.lexeme = ">=";
            u.UL = SUPEG;  /// Superieur ou egal
            return u;
        }
        else
        {
            u.lexeme = ">";
            u.UL = SUP;  /// Superieur
            return u;
        }
    }
    case '!':
    {
        carCourant = lireCar();
        if(carCourant == '=')
        {
            carCourant = lireCar();
            u.lexeme = "!=";
            u.UL = DIFF; /// Differente
            return u;
        }
        else
        {
            u.lexeme = "!";  /// Negation : NOT
            u.UL = NOT;
            return u;
        }
    }
    case '&':
    {
        carCourant = lireCar();
        if(carCourant == '&')
        {
            carCourant = lireCar();
            u.lexeme = "&&";
            u.UL = ET; /// ET
            return u;
        }
        else
        {
            u.UL = ERROR;
            u.lexeme = "Erreur '&' est attendu";
            return u;
        }
    }
    case '|':
    {
        carCourant = lireCar();
        if(carCourant == '|')
        {
            carCourant = lireCar();
            u.lexeme = "||";
            u.UL = OU;  /// OU
            return u;
        }
        else
        {
            u.UL = ERROR;
            u.lexeme = "Erreur '|' est attendu";
            return u;
        }
    }

    case '\'':
    {
        int i=0;
        char *lexeme = new char[5];
        lexeme[i++] = carCourant;
        carCourant = lireCar();
        if (carCourant == '\\')
        {
            lexeme[i++] = carCourant;
            carCourant = lireCar();
            if(carCourant!='n' && carCourant!='t' && carCourant!='b' && carCourant!='\\' && carCourant!='\''){
                u.UL = ERROR;
                return u;
            }
            lexeme[i++] = carCourant;
            carCourant = lireCar();
            lexeme[i++] = carCourant;
            lexeme[i] = '\0';
            u.lexeme = lexeme;
            u.UL = CAR;
            return u;
        }
        else if(carCourant == '\''){
            u.UL = ERROR;
            return u;
        }
        else{
            lexeme[i++] = carCourant;
            carCourant = lireCar();
            if(carCourant == '\'')
            {
                lexeme[i++] = carCourant;
                carCourant = lireCar();
                lexeme[i] = '\0';
                u.lexeme = lexeme;
                u.UL = CAR;
                return u;
            }else{
                u.UL = ERROR;
                u.lexeme = " Erreur un ' est attendu";
                return u;
            }
        }

    }

    default:
    {
        if (estChiffre(carCourant))
        {
            int j = 0;
            char *lexeme = new char [2];
            while (estChiffre(carCourant))
            {
                lexeme[j++] = carCourant;
                carCourant = lireCar();
            }
            lexeme[j] = '\0';
            u.lexeme = lexeme;
            u.UL = CONST;
            return u;
        }

        else if (estLettre(carCourant))
        {
            int lonLex = 0;
            char * lexeme;
            lexeme = new char[7];
            while (estLettre(carCourant) || estChiffre(carCourant))
            {
                lexeme[lonLex++] = carCourant;
                carCourant = lireCar();
            }

            lexeme[lonLex] = '\0';
            if (estMotCle(lexeme))
            {
                u.lexeme = lexeme;
                u.UL = MOTCLE;
                return u;
            }
            u.lexeme = lexeme;
            u.UL = IDENT;
            return u;
        }
        else
        {
            u.lexeme = "Erreur n'est pas un alphanumerique";
            u.UL = ERROR;
            return u;
        }
    }
    }
}
