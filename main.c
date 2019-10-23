#include "initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define clear() printf("\e[1;1H\e[2J\n")
#define txt(c) #c




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

int isLeaders(char* a,int type,Player *p){
    int j;
    int taille = sizeof(Leaders)/sizeof(Leader);
    Leader lead;  
    for (j = 0; j < taille; j++){
        if(strcmp(Leaders[j].nom,a)==0 && Leaders[j].Type==type){
            lead=Leaders[j];
            if(p->CE>=Leaders[j].CE){
                p->CE-=lead.CE;
                p->Pleader=lead;
                return 1;
            }
        }
    } 
    return 0;
}




void initHeader(){
    printf("ID\t Nom\t\tCE\n");
    printf("-1\tAucun choix\n");
}

void initProtection(Player *p){
    int ind=-2;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisissez votre Protection\n\n");
    initHeader();
    for(j=0;j<sizeof(Protections)/sizeof(Protection);j++){
        printf("%d\t%-20s\t%d\n",j,Protections[j].nom,Protections[j].CE);
    } 
    printf("\n");
    int choix=0;
    while(choix==0){
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);//verif
        if(ind==-1){
            choix=1;
        }else if(ind>=0 && ind <= sizeof(Protections)/sizeof(Protection)){
            choix=2;
        }
    };
    if(choix==2){
        p->Protection=Protections[ind];
        p->CE-=Protections[ind].CE;
    }else{
        Protection c;
        c.nom="Aucune";
        p->Protection=c;
    }

    free(var);
}

void initWeapon(Player *p){
    int ind=-2;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisissez votre Arme\n\n");
    printf("ID\t Nom\t\tCE\n");
    for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
        printf("%d\t%-20s\t%d\n",j,Weapons[j].nom,Weapons[j].CE);
    }
    printf("\n");
    int choix=0;
    while(choix==0){
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);//verif
        if(ind>=0 && ind < sizeof(Weapons)/sizeof(Weapon)){
            choix=1;
        }
}
    p->Pweapon=Weapons[ind];
    p->CE-=Weapons[ind].CE;
    

    free(var);
}

void initCare(Player *p){
    int ind=-2;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisissez votre Soin\n\n");
    initHeader();
    for(j=0;j<sizeof(Cares)/sizeof(Care);j++){
        printf("%d\t%-20s\t%d\n",j,Cares[j].nom,Cares[j].CE);
    } 
    printf("\n");
    int choix=0;
    while(choix==0){
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);//verif
        if(ind==-1){
            choix=1;
        }else if(ind>=0 && ind < sizeof(Cares)/sizeof(Care)){
            choix=2;
        }
    };
    if(choix==2){
        p->Pcare=Cares[ind];
        p->CE-=Cares[ind].CE;
    }else{
        Care c;
        c.nom="Aucune";
        p->Pcare=c;
    }

    free(var);
}

void buyCA(Player *p){
    int error=1;
    char *CA=malloc(20*sizeof(char));
    int CA2=p->CE;
    while(error){
        printf("Combien de crédits d'action voulez-vous acheter ? \n");
        scanf("%s",CA);
        CA2=isNumber(CA);
        if(CA2==-2) continue;
        if(CA2<=p->CE && CA2<=50){
            error=0;
            p->CA+=CA2;
            p->CE-=CA2;
        }
    }
}



void initPlayer(Player *p){
    clear();
    printf("\t\t%s\n\n",p->Pleader.nom);
    initProtection(p);
    clear();
    initCare(p);
    clear();
    initWeapon(p);
    clear();
    getchar();
    buyCA(p);
    getchar();
}

void printPlayer(Player *p){
    printf("\t%s\n\n",p->Pleader.nom);
    printf("CE : %d\nArme : %s\nProtection : %s\nSoin : %s\n\n",p->CE,p->Pweapon.nom,p->Protection.nom,p->Pcare.nom);
}

void commandes(char *command,int *exit,Player *p1,Player *p2,int inDuel){
    int i;
    int j=0;
    int h=0;
    char argv[5][50]={{0},{0}};
    if(command!=NULL){
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
       
    //printf("%s,%s,%s,%s",argv[0],argv[1],argv[2],argv[3]);
    if(strcmp(argv[0],"show")==0){
        if(*argv[1]!=0){
            clear();
            show(argv[1],argv[2]);
        }
    if(strcmp(argv[0],"help")==0){
            clear();
            printf("show [vegetables|fruits|weapons|Protections|cares] affiche la liste selectionner\n");
            printf("show [vegetable|fruit|weapon|Protections|care] affiche le n-ieme element de la liste selectionner\n");

        
        }
        else if(strcmp(argv[0],"exit")==0){
            *exit=0;        
        }
        
        else if(strcmp(argv[0],"fight")==0 && (strcmp(argv[2],"versus")==0 || strcmp(argv[2],"vs")==0)){
            int condition1=isLeaders(argv[1],0,p1) && isLeaders(argv[3],1,p2);
            int condition2=isLeaders(argv[1],1,p1) && isLeaders(argv[3],0,p2);
            if(condition1 || condition2){
                clear();
                printf("\t\tFight!\n\n");
                fight(p1,p2);
                
            }
        }else{
            printf("Error synthax\n");
            }
    }
    }else{
        getchar();
    }

    
}

void fight(Player *p1,Player *p2){
    initPlayer(p1);
    initPlayer(p2);
    int *end=(int *)malloc(sizeof(int));
    *end=1;
    while(*end==1){
        printf( "\n>");
        char *command=(char*)malloc(50*sizeof(char));
        scanf ("%m[^\n]%*c",&command);
        fightcommandes(command,p1,p2);
        free(command);
    }
}



void commandes(char *command,int *exit,Player *p1,Player *p2,int inDuel){
    int i;
    int j=0;
    int h=0;
    char argv[5][50]={{0},{0}};
    if(command!=NULL){
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
       
    //printf("%s,%s,%s,%s",argv[0],argv[1],argv[2],argv[3]);
    if(strcmp(argv[0],"show")==0){
        if(*argv[1]!=0){
            clear();
            show(argv[1],argv[2]);
        }
    if(strcmp(argv[0],"help")==0){
            clear();
            printf("show [vegetables|fruits|weapons|Protections|cares] affiche la liste selectionner\n");
            printf("show [vegetable|fruit|weapon|Protections|care] affiche le n-ieme element de la liste selectionner\n");

        
        }
        else if(strcmp(argv[0],"exit")==0){
            *exit=0;        
        }
        
        else if(strcmp(argv[0],"fight")==0 && (strcmp(argv[2],"versus")==0 || strcmp(argv[2],"vs")==0)){
            int condition1=isLeaders(argv[1],0,p1) && isLeaders(argv[3],1,p2);
            int condition2=isLeaders(argv[1],1,p1) && isLeaders(argv[3],0,p2);
            if(condition1 || condition2){
                clear();
                printf("\t\tFight!\n\n");
                fight(p1,p2);
                
            }
        }else{
            printf("Error synthax\n");
            }
    }
    }else{
        getchar();
    }

    
}





void main(){
    int *CA1=(int*)malloc(sizeof(int));
    int *CA2=(int*)malloc(sizeof(int));
    clear();
    Player *player1=(Player*)calloc(1,sizeof(Player));
    Player *player2=(Player*)calloc(1,sizeof(Player));
    player1->CE=10;
    player2->CE=7;
    printf(RED "\nCredit Player 1 : %d" YELLOW "\nCredit Player 2 : %d \n" RESET,player1->CE,player2->CE);   
    int *exit=(int *)malloc(sizeof(int));
    *exit=1;
    while(*exit==1){
        printf( "\n>");
        char *command=(char*)malloc(50*sizeof(char));
        scanf ("%m[^\n]%*c",&command);
        commandes(command,exit,player1,player2,0);
        free(command);
    }
    

}
