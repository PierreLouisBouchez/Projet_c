#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initialisation.h"

void error(){
    printf("Erreur arguments");
}
    
void show(char *a,char* ind){
    int i=atoi(ind);
    int j;
    if(strcmp(a,"vegetables")==0 || strcmp(a,"vegetable")==0){
        if(i && i>=0 && i<sizeof(Leaders)/sizeof(Leader) &&Leaders[i].Type==1){
            printf("ID\t Nom\t \tType\t Force\t Resistance\t PVmax \t CE\n");
            printf("%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Legumes",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);          
        }else{
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Leaders)/sizeof(Leader);j++){
                if(Leaders[j].Type==1){
                    printf("%d\t%s\n",j,Leaders[j].nom);
                
            }
        }
    }
    }else if(strcmp(a,"fruits")==0 || strcmp(a,"fruit")==0){
        if(i && i>=0 && i<sizeof(Leaders)/sizeof(Leader) && Leaders[i].Type==0){
            printf("ID\tNom\t\tType\t Force\t Resistance\t PVmax \t CE\n\n");
            printf("%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Fruits",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);
 
        }else{
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Leaders)/sizeof(Leader);j++){
                if(Leaders[j].Type==0){
                    printf("%d\t%-10s\n",j,Leaders[j].nom);
            }
        }
    }
    }else if(strcmp(a,"weapons")==0 || strcmp(a,"weapon")==0){
        if(i){
            if(i>=0 && i<sizeof(Weapons)/sizeof(Weapon)){
            printf("ID\tNom\t\t\tCE \t CA \t Dégats \tProbabilité\n\n");
            printf("%d\t%-20s\t%d\t%d\t%3d-%-5d \t %9d\n",i,Weapons[i].nom,Weapons[i].CE,Weapons[i].CA,Weapons[i].Degats[0],Weapons[i].Degats[1],Weapons[i].Portee);
            }else{
                error();
            }
        }else{
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
                printf("%d\t%-20s\n",j,Weapons[j].nom);
        }
    }
    }else if(strcmp(a,"protections")==0 || strcmp(a,"protection")==0){
        if(i){
            if(i>=0 && i<sizeof(Protections)/sizeof(Protection)){
            printf("Nom\t\t\tCE \t CA \tProbabilité\n\n");
            printf("%-20s\t%d\t%d\t%10d\n",Protections[i].nom,Protections[i].CE,Protections[i].CA,Protections[i].Probabilite);
            }else{
                error();
            }
        }else{
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Protections)/sizeof(Protection);j++){
                printf("%d\t%-20s\n",j,Protections[j].nom);
        }
    }
    }else if(strcmp(a,"cares")==0){
        if(i){
            if(i>=0 && i<sizeof(Cares)/sizeof(Care)){
            printf("Nom\t\t\tCE \t CA \t Volumes \t Effets\n\n");
            printf("%-20s\t%d\t%2d\t%5d\t%10d-%d\t\n",Cares[i].nom,Cares[i].CE,Cares[i].CA,Cares[i].Volumes,Cares[i].Effet[0],Cares[i].Effet[1]);
        }else{
                error();
            }
        }else{
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Cares)/sizeof(Care);j++){
                printf("%d\t%-20s\n",j,Cares[j].nom);
            }
        }
    }else{
            printf("Error, type help for syntax");
    }
}
    
void commandes(char *command,int *exit){
    int i;
    int j=0;
    int h=0;
    char argv[10][50] = {{0},{0}};
    for(i=0;i<50;i++){
        if(command[i]==' ' || command[i]=='\n'){
            j++;
            h=0;
            i++;
        }
        argv[j][h]=command[i];
        h++;
}
    
    //printf("%d",argv[2]);
    if(strcmp(argv[0],"show")==0){
        if(*argv[1]!=0){
            show(argv[1],argv[2]);
        }
        else{
            printf("Error, type help for syntax");
        }
    }
    else if(strcmp(argv[0],"help")==0){
        printf("show [vegetables|fruits|weapons|Protections|cares] affiche la liste selectionner");
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
    int *exit=(int *)malloc(sizeof(int));
    *exit=1;
    while(*exit==1){
        char * command=(char *)calloc(10,sizeof(char));
        printf("\n>");
        fgets(command, sizeof(char)*50, stdin);
        commandes(command,exit);
        
        free(command);
    }
    

    return 0;
}
