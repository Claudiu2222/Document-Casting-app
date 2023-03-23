/**
 * @file server.cpp 
 * @brief This file contains the implementation of a multithreaded server which accepts requests from clients and performs file conversion operations.
 * 
 * 
 */
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


static void *treat(void *); 
void respond(void *);

/**
 * @brief Structure representing data to be passed to a thread.
 * 
 * This struct contains the thread ID and the descriptor returned by the accept() function.
 */
typedef struct threadData
{
    int idThread;
    int cl;       
} threadData;

/**
 * @brief Receives a message from a socket and stores it in a buffer.
 * 
 * @param sd The socket descriptor to receive data from.
 * @param typeReceived The buffer to store the received data in.
 */
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
/**
*@brief Receives the hash of a file from a client over a socket connection.
*@param sd The socket descriptor.
*@param fileHash Pointer to a character array where the received hash will be stored.
*@return void
*/
void receiveHash(int sd, char *fileHash)
{
    int r = recv(sd, fileHash, TRANSFERSIZE, 0);
    if (r < 0)
    {
        printf("[server] Error receiving hash");
        exit(1);
    }
}

/**
*Converts a file from one format to another using a command line utility specified in the configuration file.
*@param conversionType the type of conversion to be performed (e.g., "pdf-txt")
*@param fileType1 the original file type
*@param fileType2 the target file type
*@param fileHash the hash of the file to be converted
*@param receivedFilePath the path to the received file
*@param convertedFilePath the path where the converted file will be saved
*/
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
/**
*Checks if a file exists at the specified path and sends a confirmation message to the client through the specified socket descriptor.
*@param convertedFilePath the path to the file
*@param sd the socket descriptor
*@return 1 if the file exists, 0 otherwise
*/
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
/**
*Processes the file received from the client by extracting the file type and hash,
*checking if it exists in the cache and if not, converting it and storing it in the cache.
*@param sd the socket descriptor of the connection with the client
*/
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
    struct sockaddr_in server; 
    struct sockaddr_in from;
    int sd; 
    int pid;
    pthread_t th[200]; // Thread identifiers
    int i = 0;

    /* Socket creation */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("[server]Eroare la socket().\n");
        return errno;
    }

    int on = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    /* Prepare the structures */
    bzero(&server, sizeof(server));
    bzero(&from, sizeof(from));

  
    /* Set the adress family of the server socket to IPv4 */
    server.sin_family = AF_INET;
    /* Bind the adress to the local IPv4 adress */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Set the port */
    server.sin_port = htons(PORT);

    /* Bind the socket to the local adress of the server */
    if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[server]Eroare la bind().\n");
        return errno;
    }

    /*  Server listens for client connections */
    if (listen(sd, 2) == -1)
    {
        perror("[server]Eroare la listen().\n");
        return errno;
    }
    /*  Clients are served concurently with the aid of threads */
    while (1)
    {
        int client;
        threadData *td; 
        socklen_t length = sizeof(from);

        printf("[server]Asteptam la portul %d...\n", PORT);
        fflush(stdout);

        /* We accept the client trying to connect to the server */
        if ((client = accept(sd, (struct sockaddr *)&from, &length)) < 0)
        {
            perror("[server]Eroare la accept().\n");
            continue;
        }

        /* Client is connected */
        td = (struct threadData *)malloc(sizeof(struct threadData));
        td->idThread = i++;
        td->cl = client;

        pthread_create(&th[i], NULL, &treat, td);
    }
};

/**
 * This function is executed by each thread created by the server to handle a client connection.
 * @param arg - a pointer to a threadData struct containing information about the thread and client connection.
 * @return NULL
 */
static void *treat(void *arg)
{
    struct threadData tdL;
    // Dereference the arg parameter to obtain the threadData struct
    tdL = *((struct threadData *)arg);
    printf("[thread]- %d - Asteptam fisierul...\n", tdL.idThread);
    fflush(stdout);

    // Detach the thread to ensure that its resources are cleaned up when it exits
    pthread_detach(pthread_self());

    respond((struct threadData *)arg);

    // Close the client socket descriptor
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