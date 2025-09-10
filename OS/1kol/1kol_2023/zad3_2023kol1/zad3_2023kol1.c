#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>

typedef struct{
    int IP;
    int numAdressesGenerated;
}pom;

int NUM_STORED_ADRESSES=100;


void* numIPgenerated(void *info){

    pom* inf=(pom*) info;
    
    int IP[4];
    sscanf(inf->IP, "%d.%d.%d.%d", &IP[0], &IP[1], &IP[2], &IP[3]);

     for (int a = IP[0]; a <= 255; a++) {
        for (int b = (a == IP[0] ? IP[1] : 0); b <= 255; b++) {    
            for (int c = (a == IP[0] && b == IP[1] ? IP[2] : 0); c <= 255; c++) {
                for (int d = (a == IP[0] && b == IP[1] && c == IP[2] ? IP[3] : 0); d <= 255; d++) { 
                   inf->numAdressesGenerated++;
                }
            }
        }
    }



pthread_exit((void*) inf); 
}



int main (int argc, char *argv[]){




    if(argc<2){
        printf("nemas dovolno argumenti bucko");
        exit(1);
    }


    int numAdresiGen=0;
    FILE *f=fopen(argv[1],"r");

    if(f==NULL){
        printf("Failed to open file!\n");
        exit(1);
    }

    pom info[NUM_STORED_ADRESSES];
    pthread_t nitki[NUM_STORED_ADRESSES];
    char IPadresi[NUM_STORED_ADRESSES][15]; int i=0;
    while(fscanf(f,"%s",IPadresi[i])==1 && i!=NUM_STORED_ADRESSES){

        info[i].IP=atoi(IPadresi[i]);
        info[i].numAdressesGenerated=0;
        pthread_create(nitki[i],NULL,&numIPgenerated, (void*) &info[i]);
        i++;
    }

    fclose(f);

    for (int j = 0; j < i; j++)
    {

        void* thread_result;
        pthread_join(nitki[j],&thread_result);
        pom* result= (pom*) thread_result;
        numAdresiGen+=result->numAdressesGenerated;
        free(result);
    }

    printf("Num of mozni adresi e %d", numAdresiGen);
    



    
     



}