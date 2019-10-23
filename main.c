#include "initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define clear() printf("\n")
//\e[1;1H\e[2J\n")
#define txt(c) #c

Player player1;
Player player2;



int isNumber(char* arg){
    int num;
    num = atoi(arg);
    if (num == 0 && arg[0] != '0')
        return -2;
    else
        return num;
}

void show(char *a,char* ind){
    int i=isNumber(ind);
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


void printPlayer(Player p){
    printf("\t%s\n\n",p.Pleader.nom);
    printf("CE : %d\nArme : %s\nProtection : %s\nSoin : %s\n\n",p.CE,p.Pweapon.nom,p.Protection.nom,p.Pcare.nom);
}


void initProtection(Player *p,int *CE){
    int ind=-2;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisissez votre Protection\n\n");
    printf("ID\t Nom\t\tCE\n");
    printf("-1\tAucun choix\n");
    for(j=0;j<sizeof(Protections)/sizeof(Protection);j++){
        printf("%d\t%-20s\t%d\n",j,Protections[j].nom,Protections[j].CE);
    } 
    printf("\n");
    int choix=0;
    int CE1;
    while(choix==0){
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);//verif
        if(ind==-1){
            choix=1;
        }else if(ind>=0 && ind < sizeof(Protections)/sizeof(Protection)){
            CE1=Protections[ind].CE;
            if( CE1 <= *CE){
                printf("Vous avez assez de points\n");
                choix=2;
            }else{
                printf("Vous n'avez que %d CE\n",*CE);
            }
            
        }
    };
    if(choix==2){
        p->Protection=Protections[ind];
        p->CE-=CE1;
        *CE-=CE1;
    }else{
        Protection c;
        c.nom="Aucune";
        p->Protection=c;
    }
    free(var);
}


void initWeapon(Player *p,int *CE){
    int ind=0;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisissez votre Arme\n\n");
    printf("ID\t Nom\t\tCE\n");
    for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
        printf("%d\t%-20s\t%d\n",j,Weapons[j].nom,Weapons[j].CE);
    }
    printf("\n");
    int choix=0;
    int CE1;
    while(choix==0){
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);//verif
        if(ind>=0 && ind < sizeof(Weapons)/sizeof(Weapon)){
            CE1=Weapons[ind].CE;
            if( CE1 <= *CE){
                printf("Vous avez assez de points\n");
                choix=1;
            }
            else{
                printf("Vous n'avez que %d CE\n",*CE);
            }
            
        }
    };
    p->Pweapon=Weapons[ind];
    p->CE-=Weapons[ind].CE;
    

    free(var);
}


void initCare(Player *p,int *CE){
    int ind=-2;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisissez votre Soin\n\n");
    printf("ID\t Nom\t\tCE\n");
    printf("-1\tAucun choix\n");
    for(j=0;j<sizeof(Cares)/sizeof(Care);j++){
        printf("%d\t%-20s\t%d\n",j,Cares[j].nom,Cares[j].CE);
    } 
    printf("\n");
    int choix=0;
    int CE1;
    while(choix==0){
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);//verif
        if(ind==-1){
            choix=1;
        }else if(ind>=0 && ind < sizeof(Cares)/sizeof(Care)){
            CE1=Cares[ind].CE;
            if( CE1 <= *CE){
                printf("Vous avez assez de points\n");
                choix=2;
            }else{
                printf("Vous n'avez que %d CE\n",*CE);
            }
            
        }
    };
    if(choix==2){
        p->Pcare=Cares[ind];
        p->CE-=CE1;
        *CE-=CE1;
    }else{
        Care c;
        c.nom="Aucune";
        p->Pcare=c;
    }

    free(var);
}

void buyCA(Player *p,int *CE){
    int error=1;
    char *CA=malloc(20*sizeof(char));
    int CA2=0;
    while(error){
        printf("Combien de crédits d'action voulez-vous acheter ? \n");
        scanf("%s",CA);
        CA2=isNumber(CA);
        if(CA2==-2) continue;
        if(CA2<=*CE && CA2<=50){
            printf("Vous avez assez de points\n");
            error=0;
            p->CA+=CA2;
            p->CE-=CA2;
        }else{
            printf("Vous n'avez que %d CE\n",p->CE);
        }
    }
}

/*
void fightcommandes(char *command,Player *p1,Player *p2){
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
    if(strcmp(argv[0],"show")==0){
        if(*argv[1]==0){
            clear();
            printPlayer(player1);
            printPlayer(player2);
        }
    }else if(strcmp(argv[0],"end")==0){
            printf("End");  
        
    }else{
            printf("Error synthax\n");
            }
    
    }else{
        getchar();
    }
}
*/

int finish(int *end){
    if (player1.CE < Weapons[0].CE || player2.CE < Weapons[0].CE){
        *end=0;
        printf("Fin de partie");
        if(player1.CE <player2.CE){
            printf("Victoire Player 2 !");
        }else{
            printf("Victoire Player 1 !");
        }
        printf("\tPlayer 1 : %d\tPlayer 2 : %d\n",player1.CE,player2.CE);
    }
}

void initPlayer(Player p,int* CE){
    clear();
    printf("\t\t%s\n\n",p.Pleader.nom);
    initProtection(&p,CE);
    printPlayer(p);
    printf("CE en cours :%d\n",*CE);
    clear();
    initCare(&p,CE);
    printPlayer(p);
    printf("CE en cours :%d\n",*CE);
    clear();
    initWeapon(&p,CE);
    printPlayer(p);
    printf("CE en cours :%d\n",*CE);
    clear();
    getchar();
    buyCA(&p,CE);
    printPlayer(p);
    printf("CE en cours :%d\n",*CE);
    getchar();
}

void fight(){
    printf("Que le duel commence");
    int CE,CE1,CE2;
    CE=50;
    CE1=player1.CE;
    CE2=player2.CE;
    if(CE1<50 || CE2<50){
        if(CE1 >= CE2){
            CE=CE2;
        }else{
            CE=CE1;
        }
    }
    printf("%d",CE);
    int findepartie=1;
    int end;;
    while(findepartie){
        finish(&findepartie);
        if(!findepartie){
            initPlayer(player1,&CE);
            initPlayer(player2,&CE);
            end=1;
            while(end==1){
                printf( "\n>");
                char *command=(char*)malloc(50*sizeof(char));
                scanf ("%m[^\n]%*c",&command);
                //fightcommandes(command);
                free(command);
            }
        }
    }
}


int isLeaders(char* c,int type){
    int i;
    for(i=0;i<sizeof(Leaders)/sizeof(Leader);i++){
        if(strcmp(Leaders[i].nom,c)==0 && Leaders[i].Type==type){
            return 1;
        }
    }
    return 0;
}

void LeaderSelection(char *name,Player *player){
    int i;
    player->Pleader.nom="Aucun";
    for(i=0;i<sizeof(Leaders)/sizeof(Leader);i++){
        if(strcmp(Leaders[i].nom,name)==0 && player->CE-Leaders[i].CE>0){
            player->Pleader=Leaders[i];
        }
    }
}



void commandes(char *command,int *exit){
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
    }
    else if(strcmp(argv[0],"help")==0){
        clear();
        printf("show [vegetables|fruits|weapons|Protections|cares] affiche la liste selectionner\n");
        printf("show [vegetable|fruit|weapon|Protections|care] affiche le n-ieme element de la liste selectionner\n");
    }
    else if(strcmp(argv[0],"exit")==0){
        *exit=0;        
    }
    else if(strcmp(argv[0],"fight")==0 && (strcmp(argv[2],"versus")==0 || strcmp(argv[2],"vs")==0)){
        int condition1=isLeaders(argv[1],0) && isLeaders(argv[3],1);
        int condition2=isLeaders(argv[1],1) && isLeaders(argv[3],0);
        if(condition1 || condition2){
            LeaderSelection(argv[1],&player1);
            LeaderSelection(argv[3],&player2);
            //printf("%s,%s",player1.Pleader.nom,player2.Pleader.nom);
            if(strcmp(player1.Pleader.nom,"Aucun")==0){
                printf("\nPlayer 1 pas assez des crédits  CE : %d \n",player1.CE);
            }
            if(strcmp(player2.Pleader.nom,"Aucun")==0){
                printf("\nPlayer 2 pas assez des crédits  CE : %d \n",player2.CE);
            }else{
                printf("\t\tFight!\n\n");
                player1.CE-=player1.Pleader.CE;
                player2.CE-=player2.Pleader.CE;
                player1.CEinit+=player1.Pleader.CE;
                player2.CEinit+=player2.Pleader.CE;
                fight();
            }
        }
    }else{
        printf("Aucune commande reconnue");
        }
    }else{
        getchar();
    }  
}

void main(){
    player1.CE=40;
    player2.CE=40;
    printf(RED "\nCredit Player 1 : %d" YELLOW "\nCredit Player 2 : %d \n" RESET,player1.CE,player2.CE);   
    int exit=1;
    while(exit==1){
        printf("\n>");
        char *command=(char*)malloc(50*sizeof(char));
        scanf ("%m[^\n]%*c",&command);
        commandes(command,&exit);
        free(command);
    }
}
