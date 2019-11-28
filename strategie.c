#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "strategie.h"

int stratexist(char *c){
    char *cpy=c;
    while(*cpy!='.' && *cpy !='\0'){
        cpy++;
    }
    if(strcmp(cpy,".strat")==0){
        return 1;
    }
    return 0;
}

Strategie * openStrat(char * filename){
    Strategie *strat=(Strategie *)malloc(sizeof(Strategie));
    char c;
    int j=0;
    int h=0;
    FILE *file;
    file=fopen(filename,"r");
    if (file == NULL)
        exit(0);
    char *ligne=(char *)malloc(sizeof(char)*40);
    fgets(ligne,40,file);
    char *one=malloc(sizeof(char)*20);
    char *two=malloc(sizeof(char)*20);
    char *three=malloc(sizeof(char)*20);
    
    one=strtok(ligne," ");
    int i=0;
    if((two=strtok(NULL," "))!=0){
       if((three=strtok(NULL," "))!=0){
           printf("trois arguments");
       }
    }
    //printf("%s,%s,%s",one,two,three);
    if(strcmp(one,"strategy")){
        strat->nom=two;
    }
    
    free(ligne);
    return strat;
}
int main()
{   
    //printf("%d\n",stratexist("strat1.strat"));
    printf("%s\n",openStrat("strat1.strat")->nom);
    return 0;
}
