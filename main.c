#include "initialisation.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "color.h"
#define str(c) #c


Player player1;
Player player2;
struct winsize w;
int endgame;

void clear(){
    printf("\x1B[1;1H\x1B[2J\n");
    }

void error(){
    printf("\n\tAucune commande reconnue tapez help pour afficher les commandes\n");
}

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
            printf("\tID\tNom\t\t\tCE \t CA \t Dégats \tPortée\n\n");
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
        error();
    }
}


void printPlayer(Player *p){
    printf(RESET "\t\tArme : %s\n",p->Pweapon.nom);
    printf("\t\tCA : %d \t Dégats : %d-%d \t Portée : %d\n",p->Pweapon.CA,p->Pweapon.Degats[0],p->Pweapon.Degats[1],p->Pweapon.Portee);
    if(p->Protection.nom=="Aucune"){
        printf("\t\tAucune protection\n");
    }else{
         printf("\t\tProtection : %s \n\t\tCA : %d \t Probabilité : %d%\n",p->Protection.nom,p->Protection.CA,p->Protection.Probabilite);
    }
    if(p->Pcare.nom=="Aucune"){
        printf("\t\tAucun soin \n");
    }else{
        printf("\t\tSoin : %s\n\t\tCA : %d \t Volumes : %d \t Effet : %d-%d\n",p->Pcare.nom,p->Pcare.CA,p->Pcare.Volumes,p->Pcare.Effet[0],p->Pcare.Effet[1]);
    }
}



void initProtection(Player *p){
        int choix;
        int CE1;
        int j;
        int ind=0;
        char *var=malloc(20*sizeof(char));
        choix=0;
        printf("\tChoisissez votre Protection\n\n\tID\t Nom\t\tCE\n\t-1\tAucun choix\n");
        for(j=0;j<sizeof(Protections)/sizeof(Care);j++){
            printf("\t%d\t%-20s\t%d\n",j,Protections[j].nom,Protections[j].CE);
        }
        do{
            printf("%s-> ",p->Pleader.nom);
            scanf("%s",var);
            ind=isNumber(var);
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
    int j;
    int choix;
    int CE1;
    char *var=malloc(20*sizeof(char));
    choix=0;
    printf("\tChoisissez votre Arme\n\n");
    printf("\tID\t Nom\t\tCE\n");
    for(j=0;j<sizeof(Weapons)/sizeof(Weapon);j++){
        printf("\t%d\t%-20s\t%d\n",j,Weapons[j].nom,Weapons[j].CE);
    }
    printf("\n");
    
    do{
        printf("%s-> ",p->Pleader.nom);
        scanf("%s",var);
        ind=isNumber(var);/*verif*/
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
        printf("\tChoisissez votre Soin\n\n\tID\t Nom\t\tCE\n\t-1\tAucun choix\n");
        for(j=0;j<sizeof(Cares)/sizeof(Care);j++){
            printf("\t%d\t%-20s\t%d\n",j,Cares[j].nom,Cares[j].CE);
        }
        do{
            printf("%s-> ",p->Pleader.nom);
            scanf("%s",var);
            ind=isNumber(var);
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
        printf("\tCombien de crédits d'action voulez-vous acheter ? Il vous reste %d CE \n\n",p->CEinit);
        printf("%s >",p->Pleader.nom);
        scanf("%s",CA);
        CA2=atoi(CA);
        if(CA2>=0 && CA2<=p->CEinit){
            res=0;
            p->CA+=CA2;
            p->CAcurrent=p->CA;
            p->CEinit-=CA2;
        }else{
            printf("Vous n'avez que %d CE\n",p->CEinit);
        }
    }while(res);
}

void hidePlayer(){
    int i,j;
    printf("\n");
    for(i=0;i<w.ws_row*5/6-2;i++){
        for(j=0;j<w.ws_col;j++){
            printf( " ");
        }
    }
}




void printTerrain(){
    int col=w.ws_col;
    int row=w.ws_row;
    int i,j,h;
    int pos1;
    int pos2;
    int row2=row*5/6;
    pos1=player1.pos*2;
    pos2=player2.pos*2;
    for(h=0;h<player1.PV/10;h++){
        printf(OGREEN " " RESET " ");
    }
    printf("PV : %3d",player1.PV);
    for(h=8;h<col-((player1.PV/10)*2+(player2.PV/10)*2)-8;h++){
        printf(" ");
    }
    printf("PV : %3d",player2.PV);
    for(h=0;h<player2.PV/10;h++){
        printf( RESET " " ORED " ");
    }
    printf(RESET "Player 1 Distance : %5d",player2.pos-player1.pos);
    for(j=25;j<col-8;j++){
            printf(" ");
    }
    printf("Player 2\n");
    for(j=1;j<pos1;j++){
        printf(" ");

    }
    if(player1.protect==1){
        printf("/\\");
    }else{
        printf("  ");
    }
    for(j=pos1;j<pos2;j++){
            printf(" ");
    }
    if(player2.protect==1){
        printf("/\\");
    }else{
        printf("  ");
    }
    for(j=pos2+2;j<col-1;j++){
            printf(" ");
    }
    for(j=1;j<pos1;j++){
            printf(" ");

    }
    printf("%s%s" ,player1.Pleader.sprite[0],player1.Pleader.sprite[1]);
    for(j=pos1;j<pos2;j++){
            printf(" ");
    }
    printf("%s%s\n" ,player2.Pleader.sprite[1],player2.Pleader.sprite[0]);
    for(j=1;j<pos1;j++){
            printf(" ");
    }
    printf("%s%s" ,player1.Pleader.sprite[2],player1.Pleader.sprite[3]);
    for(j=pos1;j<pos2;j++){
            printf(" ");
    }
    printf("%s%s\n" ,player2.Pleader.sprite[3],player2.Pleader.sprite[2]);
    for(j=1;j<pos1;j++){
            printf(" ");
    }
    printf("%s%s" ,player1.Pleader.sprite[4],player1.Pleader.sprite[5]);
    
    for(j=pos1;j<pos2;j++){
            printf(" ");
    }
    printf("%s%s\n" ,player2.Pleader.sprite[5],player2.Pleader.sprite[4]);
    



    printf(OGREEN);
    for(i=1+row2;i<row;i++){
        for(j=0;j<col;j++){
            printf(" ");
        }
    }
    
     
    printf(RESET "");
}

void move(Player *p,char * sens,int n){
    if(strcmp(sens,"forward")==0){
        if(p->CAcurrent>=n ){
            if(p==&player1 && player1.pos+n<player2.pos){
                player1.pos+=n;
                p->CAcurrent-=n;
            }else if(p==&player2 && player2.pos-n>player1.pos){
                player2.pos-=n;
                p->CAcurrent-=n;
            }
            
        }else{
            printf("Mouvement impossible\n");
        }
    }else if(strcmp(sens,"backward")==0){
        if(p->CA>=n*2 ){
            if(p==&player1 && player1.pos-n>0){
                player1.pos-=n;
                p->CAcurrent-=n*2;
            }else if(p==&player2 && player2.pos+n<w.ws_col/2){
                player2.pos+=n;
                p->CAcurrent-=n*2;
            }
            
        }else{
            printf("Mouvement impossible\n");
        }
    }
}

void useweapon(Player *p){
    float a,b,degat;
    int c;
    int r;
    p->CAcurrent-=p->Pweapon.CA;
    if(player2.pos-player1.pos<=p->Pweapon.Portee){
        r=rand()%100;
        if(p==&player1){
            
            if( r >= player2.Protection.Probabilite){
                degat=p->Pweapon.Degats[0]+rand()%(p->Pweapon.Degats[1]-p->Pweapon.Degats[0]);
                a=(100.0 + (float)p->Pleader.Force)/100.0;
                b=(100.0 - (float) player2.Pleader.Resistance)/100.0;
                c=(int) degat*a*b + 0.5;
                player2.PV-=c;
                printf("Vous infligez %d de dégats\n",c);
            }
        }else if( r >= player1.Protection.Probabilite){
                degat=p->Pweapon.Degats[0]+rand()%(p->Pweapon.Degats[1]-p->Pweapon.Degats[0]);
                a=(100.0 + (float)p->Pleader.Force)/100.0;
                b=(100.0 - (float) player1.Pleader.Resistance)/100.0;
                c=(int) degat*a*b + 0.5;
                player1.PV-=c; 
                printf("Vous infligez %d de dégats\n",c);
            }
    }else{
        printf("Hors de portée ! \n");
    }
}


void usecare(Player *p){
    int soin=(rand()%(p->Pcare.Effet[1]-p->Pcare.Effet[0]))+p->Pcare.Effet[0];
    if(p->PV+soin>=p->Pleader.PVMax){
        p->PV=p->Pleader.PVMax;
        printf("\nVous avez récuperé toute votre vie\n");
    }else{
        p->PV+=soin;
        printf("Vous récuperez %d points de vie\n",soin);
    }
}

void use(Player *p,char* arg,char* n){
    int num;
    int i;
    i=0;
    num=atoi(n);
    if(strcmp(arg,"weapon")==0){
        if(num>=1){
        
        while(i<num && p->CAcurrent-p->Pweapon.CA>=0 ){
            useweapon(p);
            i++;
        }
        }else if(p->CAcurrent-p->Pweapon.CA>=0){
            useweapon(p);
        }

    }else if(strcmp(arg,"protection")==0 && p->CAcurrent-p->Protection.CA>=0 ){
        p->protect=1;
        p->CAcurrent-=p->Protection.CA;
    }else if(strcmp(arg,"care")==0 && p->PV!=p->Pleader.PVMax){
        printf("%d,%d,%d|%d\n",p->PV,p->Pleader.PVMax,num,p->nbSoin);
        if(num>=1){
        while(i<num && p->CAcurrent-p->Pcare.CA>=0 && p->nbSoin>1){
            usecare(p);
            i++;
            p->nbSoin--;
        }
        }else if(p->CAcurrent-p->Pcare.CA>=0 && p->nbSoin>0){
            usecare(p);
            p->nbSoin--;
        }
    }else{
        printf("Commande impossible\n");
    }
}

void fightcommandes(char *command,Player *p,int *tour){
    int i;
    int j=0;
    int h=0;
    char argv[5][50]={{0},{0}};
    hidePlayer();
    if(p->CA>0){
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
            printPlayer(p);   
        }
        
    }else if(strcmp(argv[0],"use")==0){
            use(p,argv[1],argv[2]);

    }else if(strcmp(argv[0],"end")==0){
            *tour*=-1; 
        
    }else if(strcmp(argv[0],"move")==0){
        int n=isNumber(argv[2]);
        if(argv[2]!=0 && n>0){
            move(p,argv[1],n) ; 
            if(p->CAcurrent==0){
                *tour*=-1;  
            }
        }else{
            printf("mouvement immpossible\n");
        }
    }else{
        hidePlayer();
    }
    
    }else{
        
        getchar(); 
    }
    }else{
        *tour*=-1;
    }
    
    
    
}

void finish(int *end){
    if (player1.CE < 2 || player2.CE <2){
        *end=2;
        endgame=0;
        if(player1.CE < player2.CE){
            printf("\n\tVictoire Player 2 !\n");
        }else if(player1.CE > player2.CE){
            printf("\n\tVictoire Player 1 !\n");
        }else if(player1.CE == player2.CE){
            printf("Egalité parfaite");
        }
        printf("\n\tPlayer 1 : %d CE \tPlayer 2 : %d CE \n",player1.CE,player2.CE);
    }
}

int noCA(Player *p){
    return p->CAcurrent==0;
}
int leaderdead(Player *p){
    return p->PV<1;
}

void initPlayer(Player *p,int CE){
    p->PV=p->Pleader.PVMax;
    p->CA=50;
    clear();
    printf("\t\t%s\n\n",p->Pleader.nom);
    
    if(p->CEinit>=2){
        printf("\tIl vous reste %d CE\n",p->CEinit);
        initWeapon(p);
        clear();
        if(p->CEinit-(Protections[0].CE)>0){
            printf("\tIl vous reste %d CE\n",p->CEinit);
            initProtection(p);
            clear();
        }else{
            p->Protection.nom="Aucune";
        }
        if(p->CEinit-(Cares[0].CE)>0){
            printf("\tIl vous reste %d CE\n",p->CEinit);
            initCare(p);
            clear();
        }else{
            p->Pcare.nom="Aucune";
        }
        if(p->CEinit>0){
            printf("\tIl vous reste %d CE\n",p->CEinit);
            buyCA(p);
        }
    }
    getchar();
    p->CE+=p->CEinit;
}

int max(int a,int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}


void fight(){
    int CE,CE1,CE2,tour,gain;
    int saveCE1,saveCE2;
    int findepartie;
    int end;
    char *command=(char*)malloc(50*sizeof(char));
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
    end=1;
    tour=1;
    player1.pos=1;
    player2.pos=(w.ws_col/2)-2;
    finish(&end);
    player1.CE-=CE;
    player2.CE-=CE;  
    if(end==1){
        initPlayer(&player1,CE);
        initPlayer(&player2,CE);
        saveCE1=CE-player1.CEinit;
        saveCE2=CE-player2.CEinit;
        while(end==1){
            player1.protect=0;
            hidePlayer();
            printTerrain();
            player1.CAcurrent=player1.CA;
            player2.CAcurrent=player2.CA;
            player1.nbSoin=player1.Pcare.Volumes;
            player2.nbSoin=player2.Pcare.Volumes;
            while(tour==1){
                if(leaderdead(&player1) || leaderdead(&player2)){
                    tour=2;
                }else if(noCA(&player1)){
                    tour*=-1;
                }else{
                    
                    printf("%s (%d) >",player1.Pleader.nom,player1.CAcurrent);
                    scanf ("%m[^\n]%*c",&command);
                    fightcommandes(command,&player1,&tour);
                    printTerrain(); 
                }
                
            }
            player2.protect=0;
            hidePlayer();
            printTerrain();
            while(tour==-1){
                if(leaderdead(&player1) || leaderdead(&player2)){
                    tour=2;
                }else if(noCA(&player2)){
                    tour*=-1;
                }else{
                printf( "%s (%d) >",player2.Pleader.nom,player2.CAcurrent);
                scanf ("%m[^\n]%*c",&command);
                fightcommandes(command,&player2,&tour);
                printTerrain(); 
                }
                
            }
            
            if(leaderdead(&player1)){
                end=0;
                clear();
                printf("Player 1 mort\n");
                gain=5*max((saveCE1-saveCE2),1);
                player2.CE+=gain;
            }
            if(leaderdead(&player2)){
                end=0;
                clear();
                printf("Player 2 mort\n");
                gain=5*max((saveCE2-saveCE1),1);
                player1.CE+=gain;
            }
        }   
        free(command);
    }
    if(end==2){
        endgame=0;
    }
}
//5 5

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
        printf("\tfight [vegetable|fruit] versus|vs [fruit|vegetable]");
    }
    else if(strcmp(argv[0],"exit")==0){
        *exit=2;        
    }
    else if(strcmp(argv[0],"fight")==0 && (strcmp(argv[2],"versus")==0 || strcmp(argv[2],"vs")==0)){
        int condition1=isLeaders(argv[1],0) && isLeaders(argv[3],1);
        int condition2=isLeaders(argv[1],1) && isLeaders(argv[3],0);
        if(condition1 || condition2){
            LeaderSelection(argv[1],&player1);
            LeaderSelection(argv[3],&player2);
            if(strcmp(player1.Pleader.nom,"Aucun")==0){
                printf("\n\tPlayer 1 pas assez des crédits  CE : %d ,pour le champion %s \n",player1.CE ,argv[1]);
                if(player1.CE<7){
                    printf("Il n'a pas assez de CE pour continuer l'aventure\n");
                    *exit=2;
                }
            }else if(strcmp(player2.Pleader.nom,"Aucun")==0){
                printf("\n\tPlayer 2 pas assez des crédits  CE : %d ,pour le champion %s \n",player2.CE,argv[2]);
                if(player1.CE<7){
                    printf("Il n'a pas assez de CE pour continuer l'aventure\n");
                    *exit=2;
                }
            }else{
                printf("\t\tFight!\n\n");
                player1.CE-=player1.Pleader.CE;
                player2.CE-=player2.Pleader.CE;
                player1.CEinit+=player1.Pleader.CE;
                player2.CEinit+=player2.Pleader.CE;
                fight();
                *exit=0;
            }
        }
    }else{
        printf("\n\tAucune commande reconnue\n");
        }
    }else{
        getchar();
    }  
}

int main(){
    int exit;
    char *command=(char*)malloc(50*sizeof(char));
    clear();
    printf("\t\t\tB I E N V E N U E\tS U R\tF R U I T   W A R S\n\n");
    player1.CE=50;
    player2.CE=50;
    ioctl(0, TIOCGWINSZ, &w);
    endgame=1;
    while(endgame){
        exit=1;
        
        if(exit==1){

        
        printf(RED "\n\tCredit Player 1 : %d" YELLOW "\n\n\tCredit Player 2 : %d \n" RESET,player1.CE,player2.CE);
        
        while(exit==1){
            printf("\n\t>");
            scanf("%m[^\n]%*c",&command);
            commandes(command,&exit);
            free(command);
            finish(&exit);
        }
        if(exit==2){
            endgame=0;
        }
        }
    }
    printf("\n\t\tFIN DE PARTIE\n\n");
    //sleep(1);
    //printf("\n Voulez vous rejouer?\n");

    return 0;
}