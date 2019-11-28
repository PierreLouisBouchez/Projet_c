
typedef struct strategie{
    int prix;
    int CA;
    char *nom;
    char* Protection;
    char* Weapon;
    char* Care;
}Strategie;

Strategie * openStrat(char * filename);
