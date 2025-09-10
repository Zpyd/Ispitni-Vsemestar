#include <sys/wait.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char filename[100];
    char zbor;
    float procentIskoristenost;
} info;

void* countingWordsInDoc(void* kojZborFile){
    info* infor= (info*)kojZborFile;
    FILE *f = fopen(infor->filename,"r");

    if(f==NULL){
        printf("error opening file\n");
        return 1;
    }


    int numZborovi=0,numPojavi=0; char tmp[100];
    while(fscanf(f,"%s",tmp)==1){
        numZborovi++;
        if (!strcmp(tmp,infor->zbor)){ 
            numPojavi++;
        }
    }

    fclose(f);
    infor->procentIskoristenost=(numPojavi/numZborovi)*100;

    printf("%s: %d num times",infor->filename,numPojavi);
    pthread_exit((void*)infor);
}


int main(int argc, char *argv[])
{

    char zbor[100];
    char fileNames[3][100];
    if (argc < 2)
    {
        pthread_t nitki[3];
        void* result[3];
        info kojZborFile[3];
        printf("\nvnesi zbor za prevaruvanje: \n");
        scanf("%s", zbor);
        for (int i = 0; i < 3; i++)
        {
            printf("\nvnesi datoteka ime na datoteka: \n");
            scanf("%s",fileNames[i]);
            strcpy(kojZborFile[i].filename, fileNames[i]);
            strcpy(kojZborFile[i].zbor, zbor);
            pthread_create(nitki[i],NULL,&countingWordsInDoc,(void*)&kojZborFile);
        }

        for (int i = 0; i < 3; i++)
        {
            pthread_join(nitki[i], &result);
        }

        for (int i = 0; i < 3; i++)
        {
            info* res=(info*)result[i];
            printf("File: %s, Word '%s' Usage: %.2f%%\n", res->filename, res->zbor, res->procentIskoristenost);
        }
        

    }

    if (argc < 3)
    {
        pthread_t nitki[3];
        void* result[3];
        info kojZborFile[3];
        strcpy(zbor,argv[1]);
         for (int i = 0; i < 3; i++)
        {

            printf("\nvnesi datoteka ime na datoteka: \n");
            scanf("%s",fileNames[i]);
            strcpy(kojZborFile[i].filename, fileNames[i]);
            strcpy(kojZborFile[i].zbor, zbor);
            pthread_create(nitki[i],NULL,&countingWordsInDoc,(void*)&kojZborFile);
        }

        
        for (int i = 0; i < 3; i++)
        {
            pthread_join(nitki[i], &result[i]);
        }

        for (int i = 0; i < 3; i++)
        {
            info* res=(info*)result[i];
            printf("File: %s, Word '%s' Usage: %.2f%%\n", res->filename, res->zbor, res->procentIskoristenost);
        }
        
    }

    else
    {
        strcpy(zbor,argv[1]); // ne znam dali treba da se naprave proverka dali e zbor or file
        pthread_t nitki[argc-2];
        void* result[argc-2];
        info kojZborFile[argc-2];
        for (int i = 2; i < argc; i++)
        {
            strcpy(kojZborFile[i].filename, fileNames[i]);
            strcpy(kojZborFile[i].zbor, zbor);
            pthread_create(nitki[i],NULL,&countingWordsInDoc,(void*)&kojZborFile);
        }


        for (int i = 0; i < argc-2; i++)
        {
            pthread_join(nitki[i], &result[i]);
        }

        for (int i = 0; i < argc-2; i++)
        {
            info* res=(info*)result[i];
            printf("File: %s, Word '%s' Usage: %.2f%%\n", res->filename, res->zbor, res->procentIskoristenost);
        }

    }

    return 0;
}