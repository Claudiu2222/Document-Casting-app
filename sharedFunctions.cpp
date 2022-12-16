#include "sharedFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define TRANSFERSIZE 4096
void writeReceivedFile(int sd, char *savePath, char *filePath, char *fileType, int &fileNr)
{
    FILE *fp;
    sprintf(filePath, "%s/receivedFile%d.%s", savePath, fileNr, fileType);
    fileNr++;
    int r;
    long int fileSize;
    long int readBytes = 0;
    char info[TRANSFERSIZE] = {0};
    if ((fp = fopen(filePath, "wb")) == NULL)
    {
        printf("ERROR OPENING FILE");
        exit(1);
    }
    r = recv(sd, info, TRANSFERSIZE, 0);
    if (r < 0)
    {
        printf("ERROR RECEIVING FILE SIZE");
        exit(1);
    }

    info[r] = '\0';

    fileSize = strtol(info, NULL, 10);

    while (readBytes < fileSize)
    {
        r = recv(sd, info, TRANSFERSIZE, 0);
        readBytes += r;
        if (r < 0)
        {
            printf("ERROR RECEIVING FILE");
            exit(1);
        }
        else if (r == 0)
        {
            break;
        }
        // printf("Received %d and in info %d b\n", r, strlen(info));
        fwrite(info, 1, r, fp);
    }
    printf("RECV %ld | %ld   \n", readBytes, fileSize);
    fclose(fp);
}
void sendConfirmation(int sd, char *confirmation)
{
    if (send(sd, confirmation, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file confirmation");
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
long int sendFileSize(FILE *fp, int sd)
{
    fseek(fp, 0L, SEEK_END);
    long int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char szString[15] = {0};
    sprintf(szString, "%ld", sz);

    if (send(sd, szString, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file size");
        exit(1);
    }
    return sz;
}
void sendFile(FILE *fp, int sd, long int size)
{
    int sentBytes;
    char info[TRANSFERSIZE];

    long int readBytes = 0;

    while (fread(info, TRANSFERSIZE, 1, fp) != NULL)
    {
        info[strlen(info)] = '\0';
        if ((sentBytes = send(sd, info, TRANSFERSIZE, 0)) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }
        readBytes += sentBytes;
    }
    if (readBytes < size)
        if ((sentBytes = send(sd, info, size - readBytes, 0)) == -1)
        {
            perror("Error in sending file");
            exit(1);
        }
    readBytes += sentBytes;
    printf("SENT %ld | %ld   \n", readBytes, size);
    fclose(fp);
}
