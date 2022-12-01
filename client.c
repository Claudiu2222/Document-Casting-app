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
#include<string.h>
#define TRANSFERSIZE 1024
/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port;
void sendFileConvert(FILE *fp, int sd){
    sendFile(fp,sd);
}
void sendFile(FILE *fp, int sd)
{   int checker;
    char info[TRANSFERSIZE];
  // FILE *dp=fopen("test.html","wb");
    while(fgets(info,TRANSFERSIZE,fp)!=NULL)
    
    //while(fread(info,TRANSFERSIZE,1,fp)!=NULL)
    {  //fprintf(dp,"%s",info);
        
        if((checker=send(sd,info,sizeof(info),0))==-1)
     {   perror("[client] Error in sending file");
        exit(1);
    }
        printf("\nSent %d b\n",checker);
         bzero(info,TRANSFERSIZE);
        sleep(0.1);
    }
   
}
void sendFileBinary(FILE *fp, int sd)
{   int checker;
    char info[TRANSFERSIZE];
  // FILE *dp=fopen("test.html","wb");
    //while(fgets(info,TRANSFERSIZE,fp)!=NULL)
    
    while(fread(info,TRANSFERSIZE,1,fp)!=NULL)
    {  //fprintf(dp,"%s",info);
        
        if((checker=send(sd,info,sizeof(info),0))==-1)
     {   perror("[client] Error in sending file");
        exit(1);
    }
        printf("\nSent %d b\n",checker);
         bzero(info,TRANSFERSIZE);
        sleep(0.1);
    }
   
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
    char *fileName = "PopoiuClaudiuDaniel_A4_GulicaSilvian_A4_Tema2.tex";
    fp = fopen(fileName, "rb");
    if (fp  == NULL)
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
/*dfsdfsdfsd
*/