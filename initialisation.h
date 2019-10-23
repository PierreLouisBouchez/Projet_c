
#define RESET "\033[0m"

//Texte

#define BLACK    "\033[1;30m"
#define RED      "\033[1;31m"
#define GREEN    "\033[1;32m"
#define YELLOW   "\033[1;33m"
#define BLUE     "\033[1;34m"
#define PURPLE   "\033[1;35m"
#define CYAN     "\033[1;36m"
#define GREY     "\033[1;37m"

//underline

#define UBLACK "\033[4;30m"
#define URED "\033[4;31m"
#define UGREEN "\033[4;32m"
#define UYELLOW "\033[4;33m"
#define UBLUE "\033[4;34m"
#define UPURPLE "\033[4;35m"
#define UCYAN "\033[4;36m"
#define UWHITE "\033[4;37m"

//background

#define OBLACK "\033[40m"
#define ORED "\033[41m"
#define OGREEN "\033[42m"
#define OYELLOW "\033[43m"
#define OBLUE "\033[44m"
#define OPURPLE "\033[45m"
#define OCYAN "\033[46m"
#define OWHITE "\033[47m"




typedef struct {
    char *nom;
    int Type; //0 fruit,1 legumes
    int Force;
    int Resistance;
    int PVMax;
    int CE;
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
    int Probabilite;//En pourcentage

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
    int CEinit;
}Player;


Leader Leaders[]={
    {"Haricot",1,10,10,40,5},
    {"Fenouil",1, 12, 15, 40, 7},
    {"Poireau",1 ,15, 20 ,60, 10},
    {"Aubergine", 1 ,20 ,20 ,60 ,15},
    {"Courge" ,1 ,20 ,25 ,80 ,20},
    {"Carotte",1, 25, 25, 80, 25},
    {"Banane",0,10 ,10 ,40 ,5},
    {"Kiwi",0,12, 15, 40, 7},
    {"Poire",0, 15, 20, 60, 10},
    {"Pomme", 0 ,20 ,20, 60, 15},
    {"Ananas", 0, 20, 25, 80, 20},
    {"Durian", 0,25 ,25 ,80 ,25}
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