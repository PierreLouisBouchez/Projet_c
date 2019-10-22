#include "initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>





int isNumber(char* arg){
    int num;
    num = atoi(arg);
    if (num == 0 && arg[0] != '0')
        return -2;
    else
        return num;
}




void show(char *a,char* ind){
    //printf("%d\n",ind);
    int i=isNumber(ind);
    //printf("%d",i);
    int j;
    if(strcmp(a,"vegetables")==0 && i==-2){
        printf("ID\t Nom\n");
            for(j=0;j<sizeof(Leaders)/sizeof(Leader);j++){
                if(Leaders[j].Type==1){
                    printf("%d\t%s\n",j,Leaders[j].nom);
            }   }
    }else if(strcmp(a,"vegetable")==0 && i>=0 && i<sizeof(Leaders)/sizeof(Leader) &&Leaders[i].Type==1){
            printf("ID\t Nom\t \tType\t Force\t Resistance\t PVmax \t CE\n");
            printf("%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Legumes",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);          
        
    }else if(strcmp(a,"fruits")==0 && i==-2){
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Leaders)/sizeof(Leader);j++){
                if(Leaders[j].Type==0){
                    printf("%d\t%-10s\n",j,Leaders[j].nom);
            }   }
    }
    else if(strcmp(a,"fruit")==0 && i>=0 && i<sizeof(Leaders)/sizeof(Leader) && Leaders[i].Type==0){
            printf("ID\tNom\t\tType\t Force\t Resistance\t PVmax \t CE\n\n");
            printf("%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Fruits",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);
    }else if(strcmp(a,"weapon")==0 && i>=0 && i<sizeof(Weapons)/sizeof(Weapon)){
            printf("ID\tNom\t\t\tCE \t CA \t Dégats \tProbabilité\n\n");
            printf("%d\t%-20s\t%d\t%d\t%3d-%-5d \t %9d\n",i,Weapons[i].nom,Weapons[i].CE,Weapons[i].CA,Weapons[i].Degats[0],Weapons[i].Degats[1],Weapons[i].Portee);
    }else if(strcmp(a,"weapons")==0 && i==-2){
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
                printf("%d\t%-20s\n",j,Weapons[j].nom);
            }   
    }else if(strcmp(a,"protection")==0 && i>=0 && i<sizeof(Protections)/sizeof(Protection)){
            printf("Nom\t\t\tCE \t CA \tProbabilité\n\n");
            printf("%-20s\t%d\t%d\t%10d\n",Protections[i].nom,Protections[i].CE,Protections[i].CA,Protections[i].Probabilite);
    }else if(strcmp(a,"protections")==0 && i==-2){
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Protections)/sizeof(Protection);j++){
                printf("%d\t%-20s\n",j,Protections[j].nom);
        }   
    }else if(strcmp(a,"care")==0 && i>=0 && i<sizeof(Cares)/sizeof(Care)){
            printf("Nom\t\t\tCE \t CA \t Volumes \t Effets\n\n");
            printf("%-20s\t%d\t%2d\t%5d\t%10d-%d\t\n",Cares[i].nom,Cares[i].CE,Cares[i].CA,Cares[i].Volumes,Cares[i].Effet[0],Cares[i].Effet[1]);
    }else if(strcmp(a,"cares")==0 && i==-2){
            printf("ID\t Nom\n");
            for(j=0;j<sizeof(Cares)/sizeof(Care);j++){
                printf("%d\t%-20s\n",j,Cares[j].nom);
            }
    }else{
            printf("Error, type help for syntax");
    }
}

int isLeaders(char* a,int type){
    int j;
    int taille = sizeof(Leaders)/sizeof(Leader);
    for (j = 0; j < taille; j++){
        if(strcmp(Leaders[j].nom,a)==0 && Leaders[j].Type==type){
            return 1;
        }
    } 
    return 0;
}





void newleader(Player* player,char* p){
    int j;
    int taille = sizeof(Leaders)/sizeof(Leader);
    Leader lead;
    for (j = 0; j < taille; j++){
        if(strcmp(Leaders[j].nom,p)==0){
            lead=Leaders[j];
        }
    } 
    player->Pleader=lead;

}

int initProtection(Player *p){
    int ind=-2;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisir votre Protection\n");
    printf("ID\t Nom\t CE\n");
    for(j=0;j<sizeof(Protections)/sizeof(Protection);j++){
        printf("%d\t%-20s\t%d\n",j,Protections[j].nom,Protections[j].CE);
    } 
    printf("\n");
    while(!(ind>=-1 && ind <= sizeof(Protections)/sizeof(Protection) )){
        printf("%s > ",p->Pleader.nom);
        scanf("%s",var);
        if(strcmp(var,"-1")==0){
            ind=-1;
        }else{
        ind=isNumber(var);
        }
        printf("%d\n",ind);
    };
    free(var);
}

int initWeapon(Player *p){
    int ind=-2;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisir votre Arme\n");
    printf("ID\t Nom\t CE\n");
    for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
        printf("%d\t%-20s\t%d\n",j,Weapons[j].nom,Weapons[j].CE);
    } 
    printf("\n");
    while(ind<-1 || ind > sizeof(Weapons)/sizeof(Weapon)){
        
        printf("%s > ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);
        printf("%d\n",ind);
    };
    free(var);
}

void initPlayer(Player *p){
    int end=0;
    int i=0;
    while(end==0){
        while(i==0){
            initProtection(p);
            initWeapon(p);
            i=1;
        }
        end=1;
    }
}

void fight(char *p1,char* p2){
    Player *player1=(Player*)calloc(1,sizeof(Player));
    Player *player2=(Player*)calloc(1,sizeof(Player));
    newleader(player1,p1);
    newleader(player2,p2);
    initPlayer(player1);
    initPlayer(player2);
}



void commandes(char *command,int *exit){
    int i;
    int j=0;
    int h=0;
    char argv[5][50]={{0},{0}};
    for(i=0;i<strlen(command);i++){
        if(command[i]==' ' || command[i]=='\n'){
            j++;
            h=0;
            do{i++;}while(command[i]==' ');
        }
        if(isalpha(command[i]) || isdigit(command[i])){
            argv[j][h]=command[i];
            h++;
        }
    }
    //printf("%s,%s,%s,%s\",argv[0],argv[1],argv[2],argv[3]);
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
    
    else if(strcmp(argv[0],"fight")==0 && strcmp(argv[2],"versus")==0){
        int condition1=isLeaders(argv[1],0) && isLeaders(argv[3],1);
        int condition2=isLeaders(argv[1],1) && isLeaders(argv[3],0);
        if(condition1 || condition2){
            printf("\t\tFight!\n\n");
            fight(argv[1],argv[3]);
            
        };
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
        printf("\n>");
        
        char *command=malloc(50*sizeof(char));
        scanf ("%m[^\n]%*c", &command);
        commandes(command,exit);
        free(command);
    }
    

    return 0;
}
