
#ifndef SHARED_FUNCTIONS_H
#define SHARED_FUNCTIONS_H
#include<stdio.h>
long int sendFileSize(FILE* fp,int sd);
void writeReceivedFile(int sd,char* savePath,char* filePath, char* fileType, int &fileNr);
void extractTypes(char *conversionType, char *fileType1, char *fileType2);
void sendFile(FILE *fp, int sd, long int size);
void sendConfirmation(int sd, char *confirmation);
#endif
