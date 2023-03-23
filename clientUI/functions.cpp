#include "qcombobox.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include"functions.h"
#include <sys/socket.h>
#define TRANSFERSIZE 4096

/**
 * @brief Verify if the provided paths and conversion type are valid for conversion
 * 
 * @param pathOfFile QLineEdit* representing the path of the file to convert
 * @param pathOfSaveFolder QLineEdit* representing the path of the folder to save the converted file
 * @param convertFileBtn QPushButton* representing the button used to trigger the conversion process
 * @param selectTypeBox QComboBox* representing the selection box for the conversion type
 */
void  verifyIfValid(QLineEdit* pathOfFile, QLineEdit* pathOfSaveFolder, QPushButton* convertFileBtn, QComboBox* selectTypeBox){
    QString conversionType = selectTypeBox->currentText();

    QString firstType=conversionType.mid(0, conversionType.indexOf("-"));

    if(pathOfFile->text().isEmpty()==0 && pathOfSaveFolder->text().isEmpty()==0 && pathOfFile->text().endsWith(firstType))
        convertFileBtn->setEnabled(true);
    else
        convertFileBtn->setEnabled(false);
}
/**
 * @brief Extracts the hash value of a file
 * 
 * @param fileHash char* representing the hash value of the file to extract
 */
void extractFileHash(char* fileHash)
{
    int i=0;
    while(i < strlen(fileHash) && fileHash[i] != ' ')
    {
        i++;
    }
    fileHash[i]='\0';
}
/**
 * @brief Connects the signals between the path and type selection fields and the conversion button
 * 
 * @param pathOfFile QLineEdit* representing the path of the file to convert
 * @param pathOfSaveFolder QLineEdit* representing the path of the folder to save the converted file
 * @param convertFileBtn QPushButton* representing the button used to trigger the conversion process
 * @param selectTypeBox QComboBox* representing the selection box for the conversion type
 */
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
/**
 * @brief Computes the hash value of a file
 * 
 * @param fileName char* representing the name of the file to compute the hash value for
 * @param fileHash char* representing the hash value of the file
 */
void getFileHash(char* fileName,char * fileHash)
{
    char command[200]="sha256sum ";
    strcat(command,fileName);
    strcat(command," > hashFile.txt");
    system(command);

    FILE *fp;

    if ((fp = fopen("hashFile.txt", "r")) == NULL)
        {
            printf("[client] Error opening hash file\n");
            exit(1);
        }
    fread(fileHash,1024,1,fp);

    fclose(fp);

    extractFileHash(fileHash);

    system("rm hashFile.txt");

}
/**
 * @brief Receives a confirmation message from the server
 * 
 * @param sd int representing the socket descriptor to receive the message from
 * @return 1 if the server response is 'Y', 0 otherwise
 */
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

/**
 * @brief Sends the hash value of a file to the server
 * 
 * @param sd representing the socket descriptor to send the hash value to
 * @param fileName representing the name of the file to calculate the hash value for
 */
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

/**
 * @brief Sends the hash value of a file to the server
 * 
 * @param sd int representing the socket descriptor to send the hash value to
 * @param fileName char* representing the name of the file to send the hash value for
 */
void sendType(int sd, char *fileTypes)
{
    char response[TRANSFERSIZE];

    if (send(sd, fileTypes, TRANSFERSIZE, 0) == -1)
    {
        perror("[client] Error in sending file TYPE");
        exit(1);
    }

}
