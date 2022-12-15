#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include "sharedFunctions.h"

#define TRANSFERSIZE 4096

#define PORT 9000
int fileNr;
// extern int errno;

typedef struct threadData
{
    int idThread; // id-ul thread-ului
    int cl;       // descriptorul returnat de accept()
} threadData;
int min(int a, int b)
{
    return a < b ? a : b;
}
static void *treat(void *); /* functia executata de fiecare thread*/
void respond(void *);
void receiveType(int sd, char *typeReceived)
{

    int r = recv(sd, typeReceived, TRANSFERSIZE, 0);
    if (r < 0)
    {
        printf("ERROR RECEIVING TYPE");
        exit(1);
    }
    typeReceived[r] = '\0';
    printf("%s", typeReceived);
}
void receiveHash(int sd, char *fileHash)
{
    int r = recv(sd, fileHash, TRANSFERSIZE, 0);
    if (r < 0)
    {
        printf("ERROR RECEIVING HASH");
        exit(1);
    }
}

void convertFile(char *conversionType, char *fileType1, char *fileType2, char *fileHash, char *receivedFilePath, char *convertedFilePath)
{
    char command[TRANSFERSIZE];
    char utilitary[30];

    char line[100];
    FILE *fp;

    if ((fp = fopen("configuration.txt", "r")) == NULL)
    {
        printf("ERROR OPENING CONFIGURATION FILE - SERVER");
        exit(1);
    }

    while (fgets(line, 100, fp) != NULL)
    {
        if (strstr(line, conversionType) != NULL)
        {
            break;
        }
    }
    printf("\n line:%s\n", line);
    fclose(fp);
  
    int i = 0;
    while (line[i] != '"')
    {
        i++;
    }
    i++;
    int j = 0;
    while (line[i] != '"')
    {
        utilitary[j] = line[i];
        i++;
        j++;
    }
    utilitary[j] = '\0';

    sprintf(command, "%s %s %s", utilitary, receivedFilePath, convertedFilePath);
    system(command);
    // char *response="OK";
    // send(sd,response,TRANSFERSIZE,0);
    printf("---\n%s\n----", fileHash);
    printf("\n\n\n%s\n\n\n", command);
    // printf("DD |%s|--|%s| DD\n", fileType1, fileType2);
}
void processFile(int sd)
{
    FILE *fp;
    char fileType1[6];
    char fileType2[6];
    char conversionType[TRANSFERSIZE];
    char fileHash[TRANSFERSIZE];
    char receivedFilePath[TRANSFERSIZE];
    char convertedFilePath[TRANSFERSIZE];
    receiveType(sd, conversionType);

    extractTypes(conversionType, fileType1, fileType2);
    receiveHash(sd, fileHash);
    sprintf(convertedFilePath, "CachedFiles/%s/%s.%s", fileType2, fileHash, fileType2);
    // sleep(1);
    // verifyHash(fileHash);
    writeReceivedFile(sd, "ReceivedFiles", receivedFilePath, fileType1, fileNr);
    printf("%s\n", conversionType);
    printf("%s\n", fileType1);
    printf("%s\n", fileType2);
    convertFile(conversionType, fileType1, fileType2, fileHash, receivedFilePath, convertedFilePath);

  ////  if ((fp = fopen(convertedFilePath, "rb")) == NULL)
  ////  {
  ////      printf("ERROR OPENING CONVERTED FILE - SERVER");
   ////     exit(1);
  ////  }
  ////  
  ////  printf("D%s\n", convertedFilePath);
   // sendConfirmation(sd,"OK");
   printf("\n|%s|\n", convertedFilePath);
  
   if ((fp = fopen(convertedFilePath, "rb")) == NULL)
    {
        printf("ERROR OPENING FILE");
        exit(1);
    }
    long int size=sendFileSize(fp, sd);
    printf("SIZE:%ld\n",size);
    sendFile(fp, sd,size);
    // char *response="OK";
    // send(sd,response,TRANSFERSIZE,0);
    //printf("---\n%s\n----", fileHash);

    //sleep(1);
    // printf("DD |%s|--|%s| DD\n", fileType1, fileType2);
}

int main()
{
    struct sockaddr_in server; // structura folosita de server
    struct sockaddr_in from;
    int nr; // mesajul primit de trimis la client
    int sd; // descriptorul de socket
    int pid;
    pthread_t th[200]; // Identificatorii thread-urilor care se vor crea
    int i = 0;

    /* crearea unui socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[server]Eroare la socket().\n");
        return errno;
    }
    /* utilizarea optiunii SO_REUSEADDR */
    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    /* pregatirea structurilor de date */
    bzero(&server, sizeof(server));
    bzero(&from, sizeof(from));

    /* umplem structura folosita de server */
    /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;
    /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    /* utilizam un port utilizator */
    server.sin_port = htons(PORT);

    /* atasam socketul */
    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
    if (listen(sd, 2) == -1)
    {
        perror("[server]Eroare la listen().\n");
        return errno;
    }
    /* servim in mod concurent clientii...folosind thread-uri */
    while (1)
    {
        int client;
        threadData *td; // parametru functia executata de thread
        socklen_t length = sizeof(from);

        printf("[server]Asteptam la portul %d...\n", PORT);
        fflush(stdout);

        // client= malloc(sizeof(int));
        /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
        if ((client = accept(sd, (struct sockaddr *)&from, &length)) < 0)
        {
            perror("[server]Eroare la accept().\n");
            continue;
        }

        /* s-a realizat conexiunea, se astepta mesajul */

        // int idThread; //id-ul threadului
        // int cl; //descriptorul intors de accept

        td = (struct threadData *)malloc(sizeof(struct threadData));
        td->idThread = i++;
        td->cl = client;

        pthread_create(&th[i], NULL, &treat, td);

    } // while
};
static void *treat(void *arg)
{
    struct threadData tdL;
    tdL = *((struct threadData *)arg);
    printf("[thread]- %d - Asteptam mesajul...\n", tdL.idThread);
    fflush(stdout);
    pthread_detach(pthread_self());
    // while(1){
    respond((struct threadData *)arg);
    // int bytesReceived = recv(tdL.cl, NULL, 0, 0);
    // if (bytesReceived == 0 || bytesReceived == -1) //cat timp inca este conectat la client
    // {
    //    break;
    //}
    //  }
    /* am terminat cu acest client, inchidem conexiunea */

    close((intptr_t)arg);
    printf("\nTHREAD CLOSED\n");
    return (NULL);
};

void respond(void *arg)
{
    int nr, i = 0;
    struct threadData tdL;
    tdL = *((struct threadData *)arg);
    /* if (read (tdL.cl, &nr,sizeof(int)) <= 0)
            {
              printf("[Thread %d]\n",tdL.idThread);
              perror ("Eroare la read() de la client.\n");
            } */

    processFile(tdL.cl);

    printf("[Thread %d]Mesajul a fost receptionat...%d\n", tdL.idThread, nr);
}