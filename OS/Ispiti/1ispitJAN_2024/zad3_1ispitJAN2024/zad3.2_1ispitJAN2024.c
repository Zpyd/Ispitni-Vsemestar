#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#define MAX_NITKI 10
#define NIZA_LEN 1000

key_t kluc=12345;
typedef struct{
    int niza[NIZA_LEN];
    int thread_flags[MAX_NITKI];
    int izbranBroj;
    int brojNitki;
    int pominatiSite;
}pom;


int main(){

    int niza[NIZA_LEN];
    for(int i=0;i<NIZA_LEN;i++){
        printf("vnesi broj");
        scanf("%d",&niza[i]);
    }

    int id=shmget(kluc,sizeof(pom),  0644 | IPC_CREAT);
    if(id==-1){
        printf("neuspesno dobivanje pristap do memorijata");return 0;
    }
    pom *mem;
    mem=shmat(id,NULL,0);
        if(mem==(void *)-1){
        printf("neuspesno prikacuvanje na memorijata");return 0;

    }


    for (int i = 0; i < NIZA_LEN; i++)
    {
       mem->niza[i]=niza[i];
    }
    int brnitka;
    srand(time(NULL));

    while(!mem->pominatiSite){   
       do {
             brnitka = rand() % mem->brojNitki;
    } while(mem->thread_flags[brnitka]);
        mem->izbranBroj=brnitka;
    }
    shmdt(mem);
    return 0;

}