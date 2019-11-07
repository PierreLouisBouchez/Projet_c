#include "color.h"


typedef struct {
    char *nom;
    /*0 fruit,1 legumes*/
    int Type; 
    int Force;
    int Resistance;
    int PVMax;
    int CE;
    char **sprite;    
}Leader;

typedef struct
{
    char *nom;
    int CE;
    int CA;
    int Degats[2];
    int Portee;
}Weapon;

typedef struct 
{
    char *nom;
    int CE;
    int CA;
    int Probabilite;/*En pourcentage*/

}Protection;

typedef struct
{
    char *nom;
    int CE;
    int CA;
    int Volumes;
    int Effet[2];
}Care;


typedef struct{
    Leader Pleader;
    Weapon Pweapon;
    Protection Protection;
    Care Pcare;
    int CE;
    int CA;
    int CAcurrent;
    int CEinit;
    int pos;
    int protect;
    int PV;
    int nbSoin;
}Player;


char *Haricot[]={OGREEN " "RESET,RESET " ",OGREEN " "RESET,RESET " ",RESET " ",OGREEN " " RESET};
char *Fenouil[]={" ",OGREEN" " RESET,OGREEN" "RESET,OGREEN" "RESET,OWHITE" "RESET,OWHITE" " RESET};
char *Poireau[]={" ",OGREEN" " RESET," ",OGREEN" " RESET," ",OWHITE" " RESET};
char *Aubergine[]={" ",OGREEN" " RESET,OPURPLE" " RESET,OPURPLE" " RESET,OPURPLE" " RESET,OPURPLE" " RESET};
char *Courge[]={" ",OGREEN" " RESET,OGREEN" " RESET,OGREEN" " RESET,OGREEN" " RESET,OGREEN" " RESET};
char *Carotte[]={" ",OGREEN" " RESET," ",OYELLOW" " RESET," ",OYELLOW" " RESET};
char *Banane[]={RESET" "RESET,OYELLOW " " RESET,OYELLOW " " RESET," ",OYELLOW " " RESET," "};
char *Kiwi[]={" "," "," "," "," ",OGREEN" "RESET};
char *Poire[]={" "," ",OGREEN" " RESET," ",OGREEN" " RESET,OGREEN" " RESET};
char *Pomme[]={" ",OGREEN " " RESET,ORED" "RESET,ORED" "RESET,ORED" "RESET,ORED" "RESET};
char *Ananas[]={OGREEN" " RESET,OGREEN" " RESET,OYELLOW " " RESET,OYELLOW " " RESET,OYELLOW " " RESET,OYELLOW " " RESET};
char *Durian[]={" ",OYELLOW " " RESET,OGREEN" " RESET,OGREEN" " RESET,OYELLOW " " RESET,OGREEN" " RESET};

Leader Leaders[]={
    {"Haricot",1,10,10,40,5,Haricot},
    {"Fenouil",1, 12, 15, 40, 7,Fenouil},
    {"Poireau",1 ,15, 20 ,60, 10,Poireau},
    {"Aubergine", 1 ,20 ,20 ,60 ,15,Aubergine},
    {"Courge" ,1 ,20 ,25 ,80 ,20,Courge},
    {"Carotte",1, 25, 25, 80, 25,Carotte},
    {"Banane",0,10 ,10 ,40 ,5,Banane},
    {"Kiwi",0,12, 15, 40, 7,Kiwi},
    {"Poire",0, 15, 20, 60, 10,Poire},
    {"Pomme", 0 ,20 ,20, 60, 15,Pomme},
    {"Ananas", 0, 20, 25, 80, 20,Ananas},
    {"Durian", 0,25 ,25 ,80 ,25,Durian}
};

Weapon Weapons[]={
    {"Eplucheur Laser", 2 , 1 ,{1,2},2 },
    {"Mandoline Sonique", 5, 3,{1,3}, 3},
    {"Couperet Laser", 10, 5, {2,6}, 5},
    {"Hachoir Neuronique", 20, 7,{4,9}, 7},
    {"Mixeur Blaster", 30, 10,{7,12}, 11}
};

Protection Protections[]={
    {"Casque-Egouttoir", 1, 2, 25},
    {"Casque-Entonnoir", 3, 4, 40},
    {"Woklier", 5, 6, 60},
    {"Tablier-Armure", 10, 8, 80}
};
    
Care Cares[]={
    {"Humus-Neutronique", 1, 5, 4, {2,4}},
    {"Compost-Protonique", 5, 10, 3, {5,8}},
    {"Engrais-Ionique", 7, 15, 2, {8,12}}
};