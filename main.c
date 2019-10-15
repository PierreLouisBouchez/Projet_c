#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "initialisation.h"

    
void show(char *a,char* ind){
    int i=atoi(ind);
    if(strcmp(a,"vegetables")==0 || strcmp(a,"vegetable")==0)
    {
        if(i && Leaders[i].Type==1){
            printf("ID\t Nom\t \tType\t Force\t Resistance\t PVmax \t CE\n");
            printf("%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Legumes",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);          
        }else{
        printf("ID\t Nom\n");
        for(i=0;i<sizeof(Leaders)/sizeof(Champion);i++){
             if(Leaders[i].Type==1){
                 printf("%d\t%s\n",i,Leaders[i].nom);
               
        }
    }
    }
    }else if(strcmp(a,"fruits")==0 || strcmp(a,"fruit")==0){
        if(i && Leaders[i].Type==0){
            printf("ID\tNom\t\tType\t Force\t Resistance\t PVmax \t CE\n\n");
            printf("%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Fruits",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);
 
        }else{
        printf("ID\t Nom\n");
        for(i=0;i<sizeof(Leaders)/sizeof(Champion);i++){
             if(Leaders[i].Type==0){
                printf("%d\t%-10s\n",i,Leaders[i].nom);
        }}}
    }else if(strcmp(a,"weapons")==0 || strcmp(a,"weapon")==0)
    {
        if(i){
        printf("Nom\t\t\tCE \t CA \t Dégats \tProbabilité\n\n");
        printf("%-20s\t%d\t%d\t%3d-%-5d \t %9d\n",armes[i].nom,armes[i].CE,armes[i].CA,armes[i].Degats[0],armes[i].Degats[1],armes[i].Portee);

        }else{
            printf("ID\t Nom\n");
            for(i=0;i<sizeof(armes)/sizeof(Arme);i++){
            printf("%d\t%-20s\n",i,armes[i].nom);
            
            }
        }
        
                
    
    }else if(strcmp(a,"protections")==0)
    {
        printf("Nom\t\t\tCE \t CA \tProbabilité\n\n");
        for(i=0;i<sizeof(protections)/sizeof(Protection);i++){
        printf("%-20s\t%d\t%d\t%10d\n",protections[i].nom,protections[i].CE,protections[i].CA,protections[i].Probabilite);
    }

    }else if(strcmp(a,"cares")==0)
    {
        printf("Nom\t\t\tCE \t CA \t Volumes \t Effets\n\n");
        for(i=0;i<sizeof(soins)/sizeof(Soin);i++){
        printf("%-20s\t%d\t%2d\t%5d\t%10d-%d\t\n",soins[i].nom,soins[i].CE,soins[i].CA,soins[i].Volumes,soins[i].Effet[0],soins[i].Effet[1]);
    }

    }else
    {
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
        }else{
            printf("Error, type help for syntax");
        }
    }
    else if(strcmp(argv[0],"help")==0){
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
