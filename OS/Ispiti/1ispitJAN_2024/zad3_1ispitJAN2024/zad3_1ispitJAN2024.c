#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#define MAX_NITKI 10
#define NIZA_LEN 1000


//ODLUCI DA NE ODAM SO MUTEX ZATOA SO E SAMO CITANJE NEMA RACE CONDITIONS


key_t kluc=12345;
typedef struct{
    int niza[NIZA_LEN];
    int thread_flags[MAX_NITKI];
    int pominatiSite;
    int izbranBroj;
    int brojNitki;
}pom;

pom *mem;

void *prebaraj(void *t){

    while(1){
    int id = *((int *)t);
    if(mem->izbranBroj==id){
        mem->thread_flags[id]=1;
        int count=0;
        for (int i = 0; i < NIZA_LEN; i++)
        {
            if(id==mem->niza[i]){
                count++;
                //mem->thread_flags[id]=0; da se oslobode
            }
        }
        printf("%d go ima %d pati",id,count);
        break;
    }
    }
    pthread_exit(NULL);
    
}

int main(){


    int nnitki;
    printf("vnesi broj na nitki <=%d",MAX_NITKI);
    brojnit: scanf("%d",&nnitki);
    if(nnitki>MAX_NITKI){
        printf("greska vnesen broj nitki probaj pa");
        goto brojnit;
    }
    pthread_t nitki[nnitki];
    int t[nnitki];
    int id=shmget(kluc,sizeof(pom),  0644 | IPC_CREAT);
    if(id==-1){
        printf("neuspesno dobivanje pristap do memorijata");return 0;
    }
   
    mem=shmat(id,NULL,0);
        if(mem==(void *)-1){
        printf("neuspesno prikacuvanje na memorijata");return 0;
    }
    mem->brojNitki=nnitki;
    for (int i = 0; i < nnitki;i++)
    {
        t[i]=i;
        if(pthread_create(&nitki[i],NULL,prebaraj,(void *)&t[i])){
            printf("Neuspesno kreiranje na nitka %d\n",i);return 0;
        
        }
    }
    
    for (int i = 0; i < nnitki; i++)
    {
        pthread_join(nitki[i],NULL);
    }
    mem->pominatiSite=1;

    shmdt(mem);
    return 0;

}
