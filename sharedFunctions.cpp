#include "sharedFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include<string.h>
#define TRANSFERSIZE 4096
void writeReceivedFile(int sd,char* savePath,char* filePath, char* fileType,int &fileNr)
{
    FILE *fp;
    sprintf(filePath, "%s/receivedFile%d.%s",savePath,fileNr,fileType);
    printf("\n%s\n",filePath);
    fileNr++;
    int r;
    char info[TRANSFERSIZE] = {0};
    if ((fp = fopen(filePath, "wb")) == NULL)
    {
        printf("ERROR OPENING FILE");
        exit(1);
    }
    //long int size;
    r = recv(sd, info, TRANSFERSIZE, 0);
    if(r<0)
    {
        printf("ERROR RECEIVING FILE SIZE");
        exit(1);
    }
    long answer;
    info[r] = '\0';
    long int readBytes = 0;
    answer = strtol(info, NULL, 10);
    //printf("\n\n\n\n%ld DDDD\n\n\n\n", answer);
    while (readBytes < answer)
    {

        
        r = recv(sd, info, TRANSFERSIZE, 0);
        readBytes += r;
        if(r<0)
        {
            printf("ERROR RECEIVING FILE");
            exit(1);
        }
        else if (r == 0)
        {
            break;
        }
      
     //printf("Received %d and in info %d b\n", r, strlen(info));
        printf("%s\n", info);
        // fprintf(fp, "%s", info);

        fwrite(info, 1, r, fp);

        fflush(fp);
        bzero(info, TRANSFERSIZE);
        printf("RECV %ld | %ld   \n", readBytes, answer);
        
    }
   fclose(fp);
}
void sendConfirmation(int sd, char *confirmation){
       if (send(sd, confirmation, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file CONFIRMATION");
        exit(1);
    }
}
void extractTypes(char *conversionType, char *fileType1, char *fileType2)
{

    int i = 0;
    while (conversionType[i] != '-')
    {
        fileType1[i] = conversionType[i];
        i++;
    }
    fileType1[i] = '\0';
    i++;
    int j = 0;
    while (conversionType[i] != '\0')
    {
        fileType2[j] = conversionType[i];
        i++;
        j++;
    }
    fileType2[j] = '\0';
}
long int sendFileSize( FILE* fp,int sd)
{  
    fseek(fp, 0L, SEEK_END);
    long int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    printf("%ld", sz);
    char szString[15] = {0};
    sprintf(szString, "%ld", sz);
    if (send(sd, szString, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file SIZE");
        exit(1);
    }
    printf("\nSent %s b\n", szString);
    return sz;
}
void sendFile(FILE *fp, int sd, long int size)
{
    int checker;
    char info[TRANSFERSIZE];

    long int readBytes = 0;
   
    while (fread(info, TRANSFERSIZE, 1, fp)!=NULL)
    { // fprintf(dp,"%s",info);
           
           
            info[strlen(info)]='\0';
        if ((checker = send(sd, info, TRANSFERSIZE, 0)) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }
        readBytes+=checker;
        //printf("\nSent %d b\n", checker);
        //printf("\nSent %s b\n", info);
        printf("\nSent b || %ld ||  ||\n", readBytes );
       // fwrite(info, 1, sizeof(info), dp);
       
        bzero(info, TRANSFERSIZE);
    }
   // fwrite(info, 1, sizeof(info), dp);
   
    if(readBytes!=size)
      if ((checker = send(sd, info, size-readBytes, 0)) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }
        readBytes+=checker;
         printf("\nSent b || %ld || %ld ||\n", readBytes );
   // printf("\nSent %s b || %ld || %ld ||\n", info,readBytes,size);
   


    bzero(info, TRANSFERSIZE);
    fclose(fp);
}
