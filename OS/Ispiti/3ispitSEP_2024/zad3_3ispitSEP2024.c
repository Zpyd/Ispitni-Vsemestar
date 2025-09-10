#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#define MAX_NITKI 4
#define MAX_NIZA 1000

int niza[MAX_NIZA];
int max_opseg[]={0,0,0,0};
void *prebaraj(void *t){
int id = *((int *)t);
for (int i = id*250; i < id*250+250; i++)
{
    if(niza[i]>max_opseg[i]) max_opseg[id]=niza[i];
}
pthread_exit(NULL);
}


int main(int argc,char *argv[]){

if(argc<2){
    printf("nedovolono cmdl arg");
    return 1;
}

pid_t pid; int fd;
if(pid=fork()<0){
    printf("greska pri fork");
    return 1;
}

if(pid>0){
    mode_t rezim = (S_IRWXU|S_IRWXG|S_IRWXO);
    fd = open(argv[1],O_WRONLY|O_CREAT,rezim);
    if(fd==-1){printf("Ne moze da se otvori vleznata datoteka %s\n",argv[1]);return 0;}
    if(ftruncate(fd, 1000*(sizeof(int)))==-1){
    printf("neuspesno proshiruvanje na memorijata"); return 0;
    }
    dup2(fd,1);
    close(fd);
    int nizabr[MAX_NIZA];
    srand(time(NULL));
    for (int i = 0; i < MAX_NIZA; i++)
    {
        int pom=rand();
        write(fd,&pom,siezof(int));
    }
}
else{

    while(1){
        if(fd=open(argv[1],O_RDONLY)==-1){
        sleep(1);
        continue;
        }

        dup2(fd,0);
        break;
    }

    for (int i = 0; i < MAX_NIZA; i++)
    {
        if(scanf("%d",&niza[i])) {sleep(1); i--;}
    }
    close(fd);
    
    pthread_t nitki[MAX_NITKI];
    int t[4]; 
    for(int i=0;i<MAX_NITKI;i++){
        t[i]=i;
        if(pthread_create(&nitki[i],NULL,prebaraj,(void *)&t[i])){
        printf("Neuspesno kreiranje na nitka %d\n",i);return 0;
        }
    }



    for(int i=0;i<MAX_NITKI;i++){
        pthread_join(nitki[i],NULL);
    }

    int max=0;
    for (int i = 0; i < MAX_NITKI; i++)
    {
        if(max_opseg[i]>max) max=max_opseg[i];
    }
    
    printf("Najgolemiot generiran broj e %d\n",max);
    return 0;
    }
}