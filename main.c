#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char *nom;
    int Type; //0 fruit,1 legumes
    int Force;
    int Resistance;
    int PVMax;
    int CE;
}Champion;

typedef struct
{
    char *nom;
    int CE;
    int CA;
    int Degats[2];
    int Portee;
}Arme;

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
}Soin;

Champion Leaders[]={
    {"Haricot",1,10,10,40,5},
    {"Fenouil",1, 12, 15, 40, 7},
    {"Poireau",1 ,15, 20 ,60, 10},
    {"Aubergine", 1 ,20 ,20 ,60 ,15},
    {"Courgette" ,1 ,20 ,25 ,80 ,20},
    {"Carotte",1, 25, 25, 80, 25},
    {"Banane",0,10 ,10 ,40 ,5},
    {"Kiwi",0,12, 15, 40, 7},
    {"Poire",0, 15, 20, 60, 10},
    {"Pomme", 0 ,20 ,20, 60, 15},
    {"Ananas", 0, 20, 25, 80, 20},
    {"Durian", 0,25 ,25 ,80 ,25}
};

Arme armes[]={
    {"Eplucheur Laser", 2 , 1 ,{1,2},2 },
    {"Mandoline Sonique", 5, 3,{1,3}, 3},
    {"Couperet Laser", 10, 5, {2,6}, 5},
    {"Hachoir Neuronique", 20, 7,{4,9}, 7},
    {"Mixeur Blaster", 30, 10,{7,12}, 11}
};

Protection protections[]={
    {"Casque-Egouttoir", 1, 2, 25},
    {"Casque-Entonnoir", 3, 4, 40},
    {"Woklier", 5, 6, 60},
    {"Tablier-Armure", 10, 8, 80}
};
    
Soin soins[]={
    {"Humus-Neutronique", 1, 5, 4, {2,4}},
    {"Compost-Protonique", 5, 10, 3, {5,8}},
    {"Engrais-Ionique", 7, 15, 2, {8,12}}
};
    
    
    



int main(int argc, char const *argv[])
{
    int i;
    for(i=0;i<sizeof(Leaders)/sizeof(Champion);i++){
        printf("%s : %d,%d,%d,%d\n",Leaders[i].nom,Leaders[i].Type,Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);
    }
    for(i=0;i<sizeof(armes)/sizeof(Arme);i++){
        printf("%s : %d , %d , ( %d-%d ), %d\n",armes[i].nom,armes[i].CE,armes[i].CA,armes[i].Degats[0],armes[i].Degats[1],armes[i].Portee);
    }
    for(i=0;i<sizeof(protections)/sizeof(Protection);i++){
        printf("%s : %d , %d , %d\n",protections[i].nom,protections[i].CE,protections[i].CA,protections[i].Probabilite);
    }
    for(i=0;i<sizeof(soins)/sizeof(Soin);i++){
        printf("%s : %d , %d , ( %d , %d )\n",soins[i].nom,soins[i].CE,soins[i].CA,soins[i].Volumes,soins[i].Effet[0],soins[i].Effet[1]);
    }
    return 0;
}

