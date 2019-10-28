#include "initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "sprite.h"
#define clear() printf("\e[1;1H\e[2J\n")
#define txt(c) #c


Player player1;
Player player2;
struct winsize w;



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
        printf("\tID\t Nom\n");
            for(j=0;j<sizeof(Leaders)/sizeof(Leader);j++){
                if(Leaders[j].Type==1){
                    printf("\t%d\t%s\n",j,Leaders[j].nom);
            }   }
    }else if(strcmp(a,"vegetable")==0 && i>=0 && i<sizeof(Leaders)/sizeof(Leader) &&Leaders[i].Type==1){
            printf("\tID\t Nom\t \tType\t Force\t Resistance\t PVmax \t CE\n");
            printf("\t%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Legumes",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);          
        
    }else if(strcmp(a,"fruits")==0 && i==-2){
            printf("\tID\t Nom\n");
            for(j=0;j<sizeof(Leaders)/sizeof(Leader);j++){
                if(Leaders[j].Type==0){
                    printf("\t%d\t%-10s\n",j,Leaders[j].nom);
            }   }
    }
    else if(strcmp(a,"fruit")==0 && i>=0 && i<sizeof(Leaders)/sizeof(Leader) && Leaders[i].Type==0){
            printf("\tID\tNom\t\tType\t Force\t Resistance\t PVmax \t CE\n\n");
            printf("\t%d\t%-10s\t%3s\t%5d\t%10d\t%5d\t%3d\n",i,Leaders[i].nom,"Fruits",Leaders[i].Force,Leaders[i].Resistance,Leaders[i].PVMax,Leaders[i].CE);
    }else if(strcmp(a,"weapon")==0 && i>=0 && i<sizeof(Weapons)/sizeof(Weapon)){
            printf("\tID\tNom\t\t\tCE \t CA \t Dégats \tProbabilité\n\n");
            printf("\t%d\t%-20s\t%d\t%d\t%3d-%-5d \t %9d\n",i,Weapons[i].nom,Weapons[i].CE,Weapons[i].CA,Weapons[i].Degats[0],Weapons[i].Degats[1],Weapons[i].Portee);
    }else if(strcmp(a,"weapons")==0 && i==-2){
            printf("\tID\t Nom\n");
            for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
                printf("\t%d\t%-20s\n",j,Weapons[j].nom);
            }   
    }else if(strcmp(a,"protection")==0 && i>=0 && i<sizeof(Protections)/sizeof(Protection)){
            printf("\tID\tNom\t\t\tCE \t CA \tProbabilité\n\n");
            printf("\t%d\t%-20s\t%d\t%d\t%10d\n",i,Protections[i].nom,Protections[i].CE,Protections[i].CA,Protections[i].Probabilite);
    }else if(strcmp(a,"protections")==0 && i==-2){
            printf("\tID\t Nom\n");
            for(j=0;j<sizeof(Protections)/sizeof(Protection);j++){
                printf("\t%d\t%-20s\n",j,Protections[j].nom);
        }   
    }else if(strcmp(a,"care")==0 && i>=0 && i<sizeof(Cares)/sizeof(Care)){
            printf("\tID\tNom\t\t\tCE \t CA \t Volumes \t Effets\n\n");
            printf("\t%d\t%-20s\t%d\t%2d\t%5d\t%10d-%d\t\n",i,Cares[i].nom,Cares[i].CE,Cares[i].CA,Cares[i].Volumes,Cares[i].Effet[0],Cares[i].Effet[1]);
    }else if(strcmp(a,"cares")==0 && i==-2){
            printf("\tID\t Nom\n");
            for(j=0;j<sizeof(Cares)/sizeof(Care);j++){
                printf("\t%d\t%-20s\n",j,Cares[j].nom);
            }
    }else{
            printf("\tError, type help for syntax\n");
    }
}


void printPlayer(Player *p){
    printf("\t%s\n\n",p->Pleader.nom);
    printf("\tCE : %d\n\tArme : %s\n\tProtection : %s\n\tSoin : %s\n\n",p->CE,p->Pweapon.nom,p->Protection.nom,p->Pcare.nom);
}


void initProtection(Player *p){
        int choix=0;
        int CE1;
        int j;
        int ind=0;
        char *var=malloc(20*sizeof(char));
        printf("\tChoisissez votre Protection\n\n\tID\t Nom\t\tCE\n-1\tAucun choix\n");
        for(j=0;j<sizeof(Protections)/sizeof(Care);j++){
            printf("\t%d\t%-20s\t%d\n",j,Protections[j].nom,Protections[j].CE);
        }
        do{
            printf("%s-> ",p->Pleader.nom);
            scanf("%s",var);
            ind=atoi(var);//verif
            if(ind==-1){
                choix=1;
                p->Protection.nom="Aucune";
            }else if(ind>=0 && ind < sizeof(Protections)/sizeof(Care)){
                CE1=Protections[ind].CE;
                if( CE1 <= p->CEinit){
                    choix=1;
                    printf("Vous avez assez de points\n");
                    p->Protection=Protections[ind];
                    p->CEinit-=CE1;
                }else{
                    printf("Vous n'avez que %d CE disponible\n",p->CEinit);
                }
                
            }
        }while(choix==0);
    free(var);
}


void initWeapon(Player *p){
    int ind=0;
    int j=0;
    char *var=malloc(20*sizeof(char));
    printf("\tChoisissez votre Arme\n\n");
    printf("\tID\t Nom\t\tCE\n");
    for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
        printf("\t%d\t%-20s\t%d\n",j,Weapons[j].nom,Weapons[j].CE);
    }
    printf("\n");
    int choix=0;
    int CE1;
    do{
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);//verif
        if(ind>=0 && ind < sizeof(Weapons)/sizeof(Weapon)){
            CE1=Weapons[ind].CE;
            if( CE1 <= p->CEinit){
                printf("\tVous avez assez de points\n");
                choix=1;
                p->Pweapon=Weapons[ind];
                p->CEinit-=Weapons[ind].CE;
            }
            else{
                printf("\tVous n'avez que %d CE\n",p->CEinit);
            }
            
        }
    }while(choix==0);
    free(var);
}


void initCare(Player *p){
        int choix=0;
        int CE1;
        int j;
        int ind=0;
        char *var=malloc(20*sizeof(char));
        printf("\tChoisissez votre Soin\n\n\tID\t Nom\t\tCE\n-1\tAucun choix\n");
        for(j=0;j<sizeof(Cares)/sizeof(Care);j++){
            printf("%d\t%-20s\t%d\n",j,Cares[j].nom,Cares[j].CE);
        }
        do{
            printf("%s-> ",p->Pleader.nom);
            scanf("%s",var);
            ind=atoi(var);//verif
            if(ind==-1){
                choix=1;
                p->Pcare.nom="Aucune";
            }else if(ind>=0 && ind < sizeof(Cares)/sizeof(Care)){
                CE1=Cares[ind].CE;
                if( CE1 <= p->CEinit){
                    choix=1;
                    printf("\tVous avez assez de points\n");
                    p->Pcare=Cares[ind];
                    p->CEinit-=CE1;
                }else{
                    printf("\tVous n'avez que %d CE disponible\n",p->CEinit);
                }
                
            }
        }while(choix==0);
    free(var);
}

void buyCA(Player *p){
    int res=1;
    char *CA=malloc(20*sizeof(char));
    int CA2=0;

    do{
        printf("Combien de crédits d'action voulez-vous acheter ? \n Il vous reste %d CE\n",p->CEinit);
        scanf("%s",CA);
        CA2=atoi(CA);
        if(CA2>=0 && CA2<=p->CEinit){
            printf("Vous avez acheter %d crédits d'action \n",CA2);
            res=0;
            p->CA+=CA2;
            p->CEinit-=CA2;
        }else{
            printf("Vous n'avez que %d CE\n",p->CEinit);
        }
    }while(res);
}

void showPlayer(Player *p){
    int i,j;
    printf(BLACK "\e[%d;%dH Je test",w.ws_row/2,1);

}

void fightcommandes(char *command,Player *p){
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
            showPlayer(p);    
        }
    }else if(strcmp(argv[0],"end")==0){
            printf("End");  
        
    }else{
            printf("\t\tError synthax\n");
            }
    
    }else{
        getchar();
    }
}

void finish(int *end){
    if (player1.CE == 1 || player2.CE ==1){
        *end=0;
        printf("\t\tFin de partie");
        if(player1.CE < player2.CE){
            printf("\t\tVictoire Player 2 !");
        }else{
            printf("\t\tVictoire Player 1 !");
        }
        printf("\tPlayer 1 : %d\tPlayer 2 : %d\n",player1.CE,player2.CE);
    }
}

void initPlayer(Player *p){
    clear();
    printf("\t\t%s\n\n",p->Pleader.nom);
    if(p->CEinit-(Weapons[0].CE)>0){
        printf("\tIl vous reste %d CE\n",p->CEinit);
        initWeapon(p);
        printPlayer(p);
        clear();
        if(p->CEinit-(Protections[0].CE)>0){
            printf("\tIl vous reste %d CE\n",p->CEinit);
            initProtection(p);
            printPlayer(p);
            clear();
        }else{
            p->Protection.nom="Aucune";
        }
        if(p->CEinit-(Cares[0].CE)>0){
            printf("\tIl vous reste %d CE\n",p->CEinit);
            initCare(p);
            printPlayer(p);
            clear();
        }else{
            p->Pcare.nom="Aucune";
        }
        if(p->CEinit>0){
            printf("\tIl vous reste %d CE\n",p->CEinit);
            buyCA(p);
            printPlayer(p);
            
        }
    }
    getchar();
    p->CE+=p->CEinit;
}


void printTerrain(){
    int col=w.ws_col;
    int row=w.ws_row;
    int i,j;
    int pos1;
    int pos2;
    int row2=row*5/6;
    player2.pos=col-1;
    pos1=player1.pos;
    pos2=player2.pos;
    printf(OBLUE);
    for(i=0;i<w.ws_row*5/6-2;i++){
        for(j=0;j<w.ws_col;j++){
            printf(" ");
        }
    }
    //player
    for(j=0;j<pos1;j++){
            printf(" ");
    }
    printf(GREEN "%c%c",player1.Pleader.sprite[0],player1.Pleader.sprite[1]);

    for(j=pos1+2;j<pos2-1;j++){
            printf(" ");
    }
    printf("%c%c",player2.Pleader.sprite[0],player2.Pleader.sprite[1]);


    for(j=pos2+1;j<col;j++){
            printf(" ");
    }
    for(j=0;j<pos1;j++){
            printf(" ");
    }
    printf("%c%c",player1.Pleader.sprite[2],player1.Pleader.sprite[3]);

    for(j=pos1+2;j<pos2-1;j++){
            printf(" ");
    }
    printf("%c%c",player2.Pleader.sprite[2],player2.Pleader.sprite[3]);


    for(j=pos2;j<col-1;j++){
            printf(" ");
    }
    //fin

    printf(OGREEN);
    for(i=1+row2;i<row;i++){
        for(j=0;j<col;j++){
            printf(" ");
        }
    }
    
     
    printf(RESET"\e[%d;%dH",row,1);
}

void fight(){
    printf("\n\t\tQue le duel commence !!\n\n");
    int CE,CE1,CE2,tour;
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
    player1.CEinit=CE;
    player2.CEinit=CE;
    player1.CE-=CE;
    player2.CE-=CE;
    int findepartie=1;
    int end;
    
    
    while(findepartie==1){
        finish(&findepartie);
        if(findepartie==1){
            initPlayer(&player1);
            initPlayer(&player2);
            end=1;
            tour=1;
            while(end==1){
                char *command=(char*)malloc(50*sizeof(char));
                printTerrain();
                if(tour==1){
                    printf( "\n%s (%d) >",player1.Pleader.nom,player1.CA);
                    scanf ("%m[^\n]%*c",&command);
                    fightcommandes(command,&player1);
                    tour++;
                }else{
                    printf( "\n%s (%d) >",player1.Pleader.nom,player1.CA);
                    scanf ("%m[^\n]%*c",&command);
                    fightcommandes(command,&player2);
                    tour--;
                }
                
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
        printf("\tshow [vegetables|fruits|weapons|Protections|cares] affiche la liste selectionner\n");
        printf("\tshow [vegetable|fruit|weapon|Protections|care] affiche le n-ieme element de la liste selectionner\n");
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
                printf("\n\tPlayer 1 pas assez des crédits  CE : %d ,pour le champion %s \n",player1.CE ,argv[1]);
            }
            if(strcmp(player2.Pleader.nom,"Aucun")==0){
                printf("\n\tPlayer 2 pas assez des crédits  CE : %d ,pour le champion %s \n",player2.CE,argv[2]);
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
        printf("\n\tAucune commande reconnue\n");
        }
    }else{
        getchar();
    }  
}

void main(){
    player1.CE=40;
    player2.CE=40;
    ioctl(0, TIOCGWINSZ, &w);
    clear();
    printf(RED "\n\tCredit Player 1 : %d" YELLOW "\n\n\tCredit Player 2 : %d \n" RESET,player1.CE,player2.CE);
    int exit=1;
    while(exit==1){
        printf("\n\t>");
        char *command=(char*)malloc(50*sizeof(char));
        scanf ("%m[^\n]%*c",&command);
        commandes(command,&exit);
        free(command);
    }
    
}