/* cliTCPIt.c - Exemplu de client TCP
   Trimite un nume la server; primeste de la server "Hello nume".
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <string.h>
#include <arpa/inet.h>

#include <sys/stat.h>
struct stat st;

#define TRANSFERSIZE 4096
/* codul de eroare returnat de anumite apeluri */
// extern int errno;

/* portul de conectare la server*/
int port;
//void sendFile(FILE *fp, int sd);
void sendFile(FILE *fp, int sd,long int size);
int min(int a, int b)
{
    return a < b ? a : b;
}
void sendType(char *fileTypes, int sd)
{
    char response[TRANSFERSIZE];
    printf("%s \n %d\n", fileTypes, sizeof(fileTypes));
    if (send(sd, fileTypes, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file TYPE");
        exit(1);
    }
    int r = recv(sd, response,  TRANSFERSIZE, 0);
    printf("%s", response);
    if (strcmp(response, "OK") == 0)
        printf("\n---------OK\n");
    else
        printf("\n---------NAH\n");
    bzero(response,TRANSFERSIZE);
}
void sendSize(long int sz, int sd)
{
    char szString[15] = {0};
    sprintf(szString, "%ld", sz);
    if (send(sd, szString, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file TYPE");
        exit(1);
    }
}
void sendFileConvert(FILE *fp, int sd)
{
    char *response = {0};
    sendType("latex2html",sd);
  //  sleep(5);
    fseek(fp, 0L, SEEK_END);
    long int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    printf("%ld", sz);
    sendSize(sz, sd);
   // sleep(5);
    sendFile(fp, sd, sz);
    // int r =  recv(sd, response, 3, 0);
    // printf("%s",response);
   // sleep(10);
}
/*void sendFile(FILE *fp, int sd)
{
    int checker;
    char info[TRANSFERSIZE];

    // FILE *dp=fopen("test.html","wb");
    while (fgets(info, TRANSFERSIZE, fp) != NULL)

    // while(fread(info,TRANSFERSIZE,1,fp)!=NULL)
    { // fprintf(dp,"%s",info);

        if ((checker = send(sd, info, strlen(info), 0)) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }
        printf("\nSent %s b\n", info);
        bzero(info, TRANSFERSIZE);
    }
}*/
void sendFile(FILE *fp, int sd,long int size)
{
    int checker;
    char info[TRANSFERSIZE];
   // FILE *dp=fopen("test.pdf","wb");
    // while(fgets(info,TRANSFERSIZE,fp)!=NULL)

    long int readBytes = 0;
   

    while (fread(info, TRANSFERSIZE, 1, fp)!=NULL)
    { // fprintf(dp,"%s",info);
           
            readBytes+=strlen(info);
            info[strlen(info)]='\0';
        if ((checker = send(sd, info, TRANSFERSIZE, 0)) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }

        //printf("\nSent %d b\n", checker);
        //printf("\nSent %s b\n", info);
      //  printf("\nSent %s b || %ld || %ld ||\n", info,readBytes,size);
       // fwrite(info, 1, sizeof(info), dp);
       
        bzero(info, TRANSFERSIZE);
   
    } 
       // fwrite(info, 1, sizeof(info), dp);
           if ((checker = send(sd, info, strlen(info), 0)) == -1)
        {
            perror("[client] Error in sending file");
            exit(1);
        }
   // printf("\nSent %s b || %ld || %ld ||\n", info,readBytes,size);
    bzero(info, TRANSFERSIZE);
    //fclose(dp);
}

int main(int argc, char *argv[])
{
    int sd;                    // descriptorul de socket
    struct sockaddr_in server; // structura folosita pentru conectare
                               // mesajul trimis
    int nr = 0;
    char buf[10];

    /* exista toate argumentele in linia de comanda? */
    if (argc != 3)
    {
        printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
        return -1;
    }

    /* stabilim portul */
    port = atoi(argv[2]);

    /* cream socketul */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Eroare la socket().\n");
        return errno;
    }

    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(argv[1]);
    /* portul de conectare */
    server.sin_port = htons(port);

    /* ne conectam la server */
    if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        perror("[client]Eroare la connect().\n");
        return errno;
    }

    /* citirea mesajului */
    /*printf ("[client]Introduceti un numar: ");
    fflush (stdout);
    read (0, buf, sizeof(buf));
    nr=atoi(buf);*/
    FILE *fp;
    char *fileName = "dad.pdf";

    fp = fopen(fileName, "rb");

    if (fp == NULL)
    {
        perror("[client]Error in opening fileName file");
        return errno;
    }
    // scanf("%d",&nr);

    // printf("[client] Am citit %d\n",nr);

    /* trimiterea mesajului la server */
    /* if (write (sd,&nr,sizeof(int)) <= 0)
       {
         perror ("[client]Eroare la write() spre server.\n");
         return errno;
       }*/
    sendFileConvert(fp, sd);

    /* citirea raspunsului dat de server
       (apel blocant pina cind serverul raspunde) */
    /*if (read(sd, &nr, sizeof(int)) < 0)
    {
        perror("[client]Eroare la read() de la server.\n");
        return errno;
    }*/
    /* afisam mesajul primit */
    /*printf("[client]Mesajul primit este: %d\n", nr);
    while (1)
    {
    }*/
    /* inchidem conexiunea, am terminat */
    close(sd);
}