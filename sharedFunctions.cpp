/**
 * @file sharedFunctions.cpp
 * @brief This file contains the implementation of a set of functions that are shared between the client and server applications.
 */
#include "sharedFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define TRANSFERSIZE 4096

/**
 * Writes a received file from a socket to the specified save path with the given file name and file type.
 * 
 * @param sd The socket descriptor of the connected client.
 * @param savePath The path where the received file will be saved.
 * @param filePath The path of the received file.
 * @param fileType The type of the received file.
 * @param fileNr A reference to an integer that keeps track of the received file number.
 */
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
/**
 * Extracts two file types from a conversion type string separated by a hyphen.
 * 
 * @param conversionType The conversion type string containing two file types separated by a hyphen.
 * @param fileType1 A pointer to a character array that will contain the first file type.
 * @param fileType2 A pointer to a character array that will contain the second file type.
 */
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
/**
 * Gets the size of a file and sends it over a socket.
 * 
 * @param fp A pointer to the file to be sent.
 * @param sd The socket descriptor of the connected client.
 * @return The size of the file in bytes.
 */
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
/**
 * Sends a file over a socket.
 * 
 * @param fp A pointer to the file to be sent.
 * @param sd The socket descriptor of the connected client.
 * @param size The size of the file in bytes.
 */
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
