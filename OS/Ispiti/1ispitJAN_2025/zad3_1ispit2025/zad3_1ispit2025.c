#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sy8554 6                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             xxs/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MAX_NITKI 26

typedef struct{
    char znak;
    int pronajden;
}type_t;

char *p;//mapped mem

void *prebaraj(void *t){
type_t *pronajdi=malloc(sizeof(type_t));
*pronajdi = *(type_t *)t;
for(int i=0;p[i]!=EOF;i++){
    if(pronajdi->znak==p[i]){
        pronajdi->pronajden=1;
        break;
    }
}
    return (void *) pronajdi;
}

int main(int argc,char *argv[]){

    if(argc<3){
        printf("nema dovolno argumenti od cmdl");
        return 1;
    }


    key_t kluc = (key_t)argv[1];
    pid_t dete; int fd; mode_t rezim = (S_IRWXU|S_IRWXG|S_IRWXO);

    pthread_t nitki[MAX_NITKI];
    type_t t[MAX_NITKI]; int id; type_t *mem;
    id = shmget(kluc,1024,  0644 | IPC_CREAT);
        if(id==-1){
        printf("neuspesno dobivanje pristap do memorijata");return 0;
    }

    mem=shmat(id,NULL,0);
    if(mem==(void *)-1){
   printf("neuspesno prikacuvanje na memorijata");return 0;

}

    dete = fork();
    if(dete==0){
     
    if((fd = open(argv[2],O_RDWR,rezim))==-1){
    printf("neuspesno otvoranje na datotekata"); return 0;
    }

    p = mmap(NULL,getpagesize(fd),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p==MAP_FAILED){
    printf("neuspesno mapiranje na memorijata"); return 0;
    }

    for(int i=0;i<MAX_NITKI;i++){
        t[i].znak='a'+i;
        if(pthread_create(&nitki[i],NULL,prebaraj,(void *)&t[i])){
        printf("Neuspesno kreiranje na nitka %d\n",i);return 0;
        }
    }


    for(int i=0;i<MAX_NITKI;i++){
        void *rez;
        pthread_join(nitki[i],&rez);
        mem[i]=*(type_t *)rez;
        free(rez);
    }
    munmap(p,__getpagesize());
    
    }
    wait(NULL);
    for(int i=0;i<MAX_NITKI;i++){
        if(mem[i].pronajden){
            print("Bukvata: %c e pronajdena",mem[i].znak);
        }
        print("Bukvata: %c ne e pronajdena",mem[i].znak);
    }
    shmdt(mem);
    return 0;
    }
