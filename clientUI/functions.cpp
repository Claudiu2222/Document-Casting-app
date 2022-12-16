#include "qcombobox.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include"functions.h"
#include <sys/socket.h>
#define TRANSFERSIZE 4096

void  verifyIfValid(QLineEdit* pathOfFile, QLineEdit* pathOfSaveFolder, QPushButton* convertFileBtn, QComboBox* selectTypeBox){
    QString conversionType = selectTypeBox->currentText();

    QString firstType=conversionType.mid(0, conversionType.indexOf("-"));

    if(pathOfFile->text().isEmpty()==0 && pathOfSaveFolder->text().isEmpty()==0 && pathOfFile->text().endsWith(firstType))
        convertFileBtn->setEnabled(true);
    else
        convertFileBtn->setEnabled(false);
}

void extractFileHash(char* fileHash)
{
    int i=0;
    while(i < strlen(fileHash) && fileHash[i] != ' ')
    {
        i++;
    }
    fileHash[i]='\0';
}
void connectSignalsFile(QLineEdit* pathOfFile, QLineEdit* pathOfSaveFolder, QPushButton* convertFileBtn, QComboBox* selectTypeBox ){
    QObject::connect(pathOfFile, &QLineEdit::textChanged, [pathOfFile, pathOfSaveFolder,  convertFileBtn, selectTypeBox]() {
        verifyIfValid(pathOfFile, pathOfSaveFolder, convertFileBtn, selectTypeBox);
    });
    QObject::connect(pathOfSaveFolder, &QLineEdit::textChanged, [pathOfFile, pathOfSaveFolder,  convertFileBtn, selectTypeBox]() {
        verifyIfValid(pathOfFile, pathOfSaveFolder,convertFileBtn, selectTypeBox);
    });
    QObject::connect(selectTypeBox, &QComboBox::currentTextChanged, [pathOfFile, pathOfSaveFolder,  convertFileBtn, selectTypeBox]() {
        verifyIfValid(pathOfFile, pathOfSaveFolder,  convertFileBtn, selectTypeBox);
    });
}
void getFileHash(char* fileName,char * fileHash)
{
    char command[200]="sha256sum ";
    strcat(command,fileName);
    strcat(command," > hashFile.txt");
    system(command);

    FILE *fp;
    fp = fopen("hashFile.txt", "r");

    fread(fileHash,1024,1,fp);

    fclose(fp);

    extractFileHash(fileHash);

    system("rm hashFile.txt");

}
int receiveConfirmation(int sd){
    char serverResponse[1];
    int r = recv(sd, serverResponse, 1, 0);
    if(r<0)
    {
        printf("[client] ERROR RECEIVING SEVER RESPONSE");
        exit(1);
    }
    if(serverResponse[0]=='Y')
    {
        return 1;
    }
    else return 0;

}
void sendFileHash(int sd, char* fileName)
{
    char fileHash[1024]={0};
    getFileHash(fileName,fileHash);
    if (send(sd, fileHash, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file HASH");
        exit(1);
    }
}
void sendType(int sd, char *fileTypes)
{
    char response[TRANSFERSIZE];

    if (send(sd, fileTypes, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file TYPE");
        exit(1);
    }

}
