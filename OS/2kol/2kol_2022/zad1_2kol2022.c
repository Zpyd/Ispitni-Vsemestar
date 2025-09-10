#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include <sys/wait.h>

int main(int argc,char argv[]){
    printf("vnesi kolku pati da se izvrisi programata");
    
    int Z;
    scanf("%d",&Z);
    pid_t cid;
    key_t kluc=1234;
    char* mem;

    int id=shmget(kluc,5000, 0644 | IPC_CREAT | IPC_EXCL);
    if(id==-1){
        printf("failed to get access to shared memory"); return 0;
    }

    for (int i = 0; i < Z; i++)
    {
        if(cid==0)break;
        cid=fork();
    }

    if(cid==0){
        //what is considered
        //shmid??? is it the key???
        //how do u insert stuff in the shared memory ???
        
        void* shmaddr;
        mem = shmat(id,NULL,0);
        if(mem==(void*)-1){
            printf("neuspesno dobivanje pristap do memorijata"); return 0;
        }

        
        if(shmdt(id)){
            printf("se okej dealocirano here");        };

    }


    

    shmctl(id,IPC_RMID,0);


}