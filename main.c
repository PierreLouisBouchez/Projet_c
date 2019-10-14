#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    
    
    
void commandes(char *command,int *exit){
    int i;
    int j=0;
    int h=0;
    char argv[5][50] = {{0},{0}};
    for(i=0;i<50;i++){
        //printf("%c",command[i]);
        if(command[i]==' ' || command[i]=='\n'){
            j++;
            h=0;
            i++;
        }
        argv[j][h]=command[i];
        h++;
        
         
    }
    for(i=0;i<j;i++)
        printf("%s\n",argv[i]);

    if(strcmp(argv[0],"help")==0){
        printf("show [vegetables|fruits|weapons|protections|cares] affiche la liste selectionner");
    }
    else if(strcmp(argv[0],"exit")==0){
        *exit=0;        
    }
    
}


int main()
{
    int *CA1=(int*)malloc(sizeof(int));
    int *CA2=(int*)malloc(sizeof(int));
    *CA1=1000;
    *CA2=1000;
    printf("Credit player 1 : %d  \nCredit player 2 : %d\n",*CA1,*CA2);
    /*
    int i;
    for(i=0;i<sizeof(Leaders)/sizeof(Champion);i++){
        printf("%s : %d , %d , %d , %d , %d\n",Leaders[i].nom,Leaders[i].Type,Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);
    }
    for(i=0;i<sizeof(armes)/sizeof(Arme);i++){
        printf("%s : %d , %d , ( %d-%d ), %d\n",armes[i].nom,armes[i].CE,armes[i].CA,armes[i].Degats[0],armes[i].Degats[1],armes[i].Portee);
    }
    for(i=0;i<sizeof(protections)/sizeof(Protection);i++){
        printf("%s : %d , %d , %d\n",protections[i].nom,protections[i].CE,protections[i].CA,protections[i].Probabilite);
    }
    for(i=0;i<sizeof(soins)/sizeof(Soin);i++){
        printf("%s : %d , %d , %d( %d , %d )\n",soins[i].nom,soins[i].CE,soins[i].CA,soins[i].Volumes,soins[i].Effet[0],soins[i].Effet[1]);
    }
    */
    
    int *exit=(int *)malloc(sizeof(int));
    *exit=1;
while(*exit==1){
    char * command=(char *)calloc(10,sizeof(char));
    printf("\n>");
    fgets(command, sizeof(char)*50, stdin);
    //printf("-->%s",command);
    commandes(command,exit);
    //sscanf(command, "%[^\n]", command);
    
    free(command);
    }
    

    return 0;
}

