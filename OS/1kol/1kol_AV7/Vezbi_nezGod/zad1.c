#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

typedef struct{
    int randNum;
    int flag;
}pom;

int niza[100];

void* promena(void* num){
    pom* info=(pom*) num;
    
    for (int i = 0,j=0; j < info->randNum; i++,j++)
    {
       if(i==100){
        i=0;
       }
        if(info->flag){
            niza[i]+=1;
        }
        else{
            niza[i]-=0;
        }
    }
        
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){

int brNitki;
printf("vnesi num of Nitki");
scanf("%d",&brNitki);


pid_t cid=fork();

if (cid==0)
{
    for (int i = 0; i < 100; i++)
    {
        niza[i]=0;
    }
    
    pom info[brNitki];
    pthread_t nitki[brNitki];
    for (int i = 0; i < brNitki; i++)
    {
        srand(time(0));
        
        if(i<brNitki/2){
            info[i].flag=1;
        }else{
            info[i].flag=0;
        }

        info[i].randNum=rand()%501;
        pthread_create(nitki[i],NULL,&promena,(void*) &info[i]);    

    }

    for (int i = 0; i < brNitki; i++)
    {
        pthread_join(nitki[i],NULL);
    }
    
    
}

else{

    waitpid(cid,NULL,0);//or just wait(NULL) oti e 1 kid
    int promeneti=0;
    for (int i = 0; i < 100; i++)
    {
        if(niza[i]!=0){
            promeneti++;
        }
    }
    
}

}

