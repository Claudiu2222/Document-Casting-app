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

#define TRANSFERSIZE 4096

#define PORT 9000
int fileNr;
extern int errno;

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
void receiveType(int sd, char *typeReceived2)
{
    char typeReceived[TRANSFERSIZE];
    int r = recv(sd, typeReceived, TRANSFERSIZE, 0);
    printf("%s", typeReceived);

    if (strcmp(typeReceived, "latex2html") == 0)
    {
        char response[TRANSFERSIZE] = "OK";
        if (send(sd, response, TRANSFERSIZE, 0) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }
        bzero(response, TRANSFERSIZE);
    }
    else
    {
        char response[TRANSFERSIZE] = "NAH";
        if (send(sd, response, TRANSFERSIZE, 0) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }
        bzero(response, TRANSFERSIZE);
    }
}
void receiveSendFile(int sd)
{
    char *typeReceived = "";
    receiveType(sd, typeReceived);
    // sleep(1);
    writeRecvInfo(sd);
    // char *response="OK";
    // send(sd,response,TRANSFERSIZE,0);
}
void writeRecvInfo(int sd)
{
    FILE *fp;
    char fileName[50];
    sprintf(fileName, "codNumars%d.pdf", fileNr);
    fileNr++;
    int r;
    char info[TRANSFERSIZE] = {0};
    if ((fp = fopen(fileName, "wb")) == NULL)
    {
        printf("ERR");
        exit(1);
    }
    long int size;
    r = recv(sd, info, TRANSFERSIZE, 0);
    char *remaining;
    long answer;
    info[r] = '\0';
    long int readBytes = 0;
    answer = strtol(info, &remaining, 10);
    printf("%ld", answer);
    while (readBytes < answer)
    {

        r = recv(sd, info, TRANSFERSIZE, 0);

        readBytes += r;
        if (r <= 0)
        {

            printf("Received %d and in info %d b\n", r, strlen(info));
            fflush(fp);
            fclose(fp);
            bzero(info, TRANSFERSIZE);
            return;
        }
        printf("Received %d and in info %d b\n", r, strlen(info));
        printf("%s\n", info);
        // fprintf(fp, "%s", info);

        fwrite(info, 1, r, fp);

        fflush(fp);
        bzero(info, TRANSFERSIZE);
        printf("%ld | %ld", readBytes, answer);
    }
}
int main()
{
    struct sockaddr_in server; // structura folosita de server
    struct sockaddr_in from;
    int nr; // mesajul primit de trimis la client
    int sd; // descriptorul de socket
    int pid;
    pthread_t th[2]; // Identificatorii thread-urilor care se vor crea
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
        int length = sizeof(from);

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
    respond((struct threadData *)arg);
    /* am terminat cu acest client, inchidem conexiunea */

    close((intptr_t)arg);
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

    char *fromType;
    char *toType;
    receiveSendFile(tdL.cl);

    printf("[Thread %d]Mesajul a fost receptionat...%d\n", tdL.idThread, nr);

    /*pregatim mesajul de raspuns */
    // nr++;
    // printf("[Thread %d]Trimitem mesajul inapoi...%d\n",tdL.idThread, nr);

    /* returnam mesajul clientului */
    //  if (write (tdL.cl, &nr, sizeof(int)) <= 0)
    // 	{
    // 	 printf("[Thread %d] ",tdL.idThread);
    // 	 perror ("[Thread]Eroare la write() catre client.\n");
    // 	}
    // else
    // 	printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread);
}
