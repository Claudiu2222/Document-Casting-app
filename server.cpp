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

static void *treat(void *); /* functia executata de fiecare thread*/
void respond(void *);
typedef struct threadData
{
    int idThread; // id-ul thread-ului
    int cl;       // descriptorul returnat de accept()
} threadData;

void receiveType(int sd, char *typeReceived)
{

    int r = recv(sd, typeReceived, TRANSFERSIZE, 0);
    if (r < 0)
    {
        printf("[server] Error receiving type");
        exit(1);
    }
    typeReceived[r] = '\0';
    printf("\nConversion Type:%s\n", typeReceived);
}
void receiveHash(int sd, char *fileHash)
{
    int r = recv(sd, fileHash, TRANSFERSIZE, 0);
    if (r < 0)
    {
        printf("[server] Error receiving hash");
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
        printf("[server] Error opening configuration file");
        exit(1);
    }

    while (fgets(line, 100, fp) != NULL)
    {
        if (strstr(line, conversionType) != NULL)
        {
            break;
        }
    }
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

    if (strcmp(conversionType, "tex-html") == 0)
        sprintf(command, "%s -dir %s/%s/ %s", utilitary, "CachedFiles/html", fileHash, receivedFilePath);
    else if (strcmp(conversionType, "asp-php") == 0)
        sprintf(command, "%s -o %s/%s.%s %s", utilitary, "CachedFiles/php", fileHash, fileType2, receivedFilePath);
    else
        sprintf(command, "%s %s %s", utilitary, receivedFilePath, convertedFilePath);
    printf("%s command", command);
    system(command);
    printf(" |T1: %s|--|T2: %s|\n", fileType1, fileType2);
}
int doesFileExist(char *convertedFilePath, int sd)
{
    if (access(convertedFilePath, F_OK) == 0)
    {
        if (send(sd, "Y", 1, 0) == -1)
        {
            perror("[server] Error in sending confirmation to client");
            exit(1);
        }
        return 1;
    }
    else
    {
        if (send(sd, "N", 1, 0) == -1)
        {
            perror("[server] Error in sending confirmation to client");
            exit(1);
        }
        return 0;
    }
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
    if (strcmp(conversionType, "tex-html") != 0)
        sprintf(convertedFilePath, "CachedFiles/%s/%s.%s", fileType2, fileHash, fileType2);
    else
    {
        char commandMkdir[TRANSFERSIZE];
        sprintf(commandMkdir, "mkdir CachedFiles/%s/%s", fileType2, fileHash);
        system(commandMkdir);
        sprintf(convertedFilePath, "CachedFiles/%s/%s/index.html", fileType2, fileHash);
    }
    if (doesFileExist(convertedFilePath, sd) == 0)
    {
        writeReceivedFile(sd, "ReceivedFiles", receivedFilePath, fileType1, fileNr);
        printf("[server] File does NOT exist in cache\n");
        convertFile(conversionType, fileType1, fileType2, fileHash, receivedFilePath, convertedFilePath);

        char removeCommand[TRANSFERSIZE];
        sprintf(removeCommand, "rm %s", receivedFilePath);
        system(removeCommand);
    }
    else
    {
        printf("File DOES exist in cache\n");
    }
    printf("\n \n %s \n \n", convertedFilePath);
    if ((fp = fopen(convertedFilePath, "rb")) == NULL)
    {
        printf("[server] Error opening converted file\n");
        exit(1);
    }
    long int size = sendFileSize(fp, sd);

    sendFile(fp, sd, size);
}

int main()
{
    struct sockaddr_in server; // structura folosita de server
    struct sockaddr_in from;
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

    /* este atasat socketul */
    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    /*  serverul asculta daca vin clienti sa se conecteze*/
    if (listen(sd, 2) == -1)
    {
        perror("[server]Eroare la listen().\n");
        return errno;
    }
    /*  clientii serviti in mod concurent -> folosind thread-uri */
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
        td = (struct threadData *)malloc(sizeof(struct threadData));
        td->idThread = i++;
        td->cl = client;

        pthread_create(&th[i], NULL, &treat, td);
    }
};
static void *treat(void *arg)
{
    struct threadData tdL;
    tdL = *((struct threadData *)arg);
    printf("[thread]- %d - Asteptam fisierul...\n", tdL.idThread);
    fflush(stdout);
    pthread_detach(pthread_self());

    respond((struct threadData *)arg);

    close((intptr_t)arg);
    printf("\n THREAD CLOSED \n");
    return (NULL);
};

void respond(void *arg)
{
    struct threadData tdL;
    tdL = *((struct threadData *)arg);
    processFile(tdL.cl);
    printf("[Thread %d]Fisierul a fost convertit si trimis...\n", tdL.idThread);
}