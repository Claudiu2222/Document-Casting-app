#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
#include<cstring>
#include<QFileDialog>
#include"QCloseEvent"
#include"functions.h"
#include"../sharedFunctions.h"
#define TRANSFERSIZE 4096
int port;
int fileNr;
int sd; // Socket descriptor
/**
 * @brief Constructs a new MainWindow object.
 *
 * It initializes the user interface and sets up connections between signals and slots. It also sets the focus to this window and configures the user interface.
 *
 * @param parent The parent widget of this window.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocus();
    configureUi();
    connectFileDialogsToBtns();

    connectSignalsFile(ui->pathOfFile,ui->pathOfSaveFolder,ui->convertFileBtn,ui->selectTypeBox);
    QObject::connect(ui->convertFileBtn, &QPushButton::clicked,this,&MainWindow::convertFile);
}
void MainWindow::connectFileDialogsToBtns(){

    QLineEdit *lineEditPathFile = ui->pathOfFile;
    QLineEdit *lineEditPathFolder = ui->pathOfSaveFolder;
    QObject::connect(ui->selectFileButton, &QPushButton::clicked, [lineEditPathFile]() {
        // Show the file dialog and get the selected file
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Select File", "", "Files (*.*)");

        // Set the text of the line edit to the selected file's path
        lineEditPathFile->setText(fileName);
    });
    QObject::connect(ui->selectFolderButton, &QPushButton::clicked, [lineEditPathFolder]() {
        // Show the file dialog and get the selected file
        QString fileName = QFileDialog::getExistingDirectory(nullptr, "Select Folder", "", QFileDialog::ShowDirsOnly);

        // Set the text of the line edit to the selected file's path
        lineEditPathFolder->setText(fileName);
    });

}
void MainWindow::convertFile()
{
     ui->infoMessage->setText(" ");
     ui->infoMessage->repaint();

    if(connectToServer()==2)
        return;

    FILE *fp;
    char filePath[TRANSFERSIZE];
    char savePath[TRANSFERSIZE];
    char *response = {0};
    char conversionType[TRANSFERSIZE];
    char fileType1[10];
    char fileType2[10];
    long int sizeOfFile;
    strcpy(filePath,ui->pathOfFile->text().toUtf8().data());
    strcpy(conversionType,ui->selectTypeBox->currentText().toUtf8().data());
    strcpy(savePath,ui->pathOfSaveFolder->text().toUtf8().data());
    fp = fopen(filePath, "rb");

    if (fp == NULL)
    {
        perror("[client]Error in opening file");
        exit(1);
    }


    sendType(sd,conversionType);
    sendFileHash(sd,filePath);

    if(receiveConfirmation(sd)==0)
    {
    sizeOfFile= ::sendFileSize(fp,sd);
    ::sendFile(fp, sd, sizeOfFile);}

    ::extractTypes(conversionType,fileType1,fileType2);
    ::writeReceivedFile(sd,savePath,filePath,fileType2,fileNr);
    ::close(sd);
    ui->infoMessage->setText("FILE TRANSFER COMPLETED");
}
/**
*@brief Attempts to connect to a server using the IP address and port specified in the user interface.
*If the connection is successful, the function returns 1. If the connection fails, the function sets the "infoMessage" label in the user interface to "CAN'T CONNECT TO SERVER" and returns 2.
*@return Returns 1 if the connection is successful, or 2 if the connection fails.
*/
int MainWindow::connectToServer(){


    QLineEdit *portInput = ui->portInput;


    struct sockaddr_in server; //Structure used for connecting

    port = portInput->text().toInt();

    /*Socket creation*/
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Eroare la socket().\n");
        return 2;
    }

    
    server.sin_family = AF_INET;
    
    server.sin_addr.s_addr = inet_addr(ui->ipAdressInput->text().toUtf8().data());
    
    server.sin_port = htons(port);

    if (::connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        ui->infoMessage->setText("CAN'T CONNECT TO SERVER");
        ui->infoMessage->setStyleSheet("color:red;border:0px;");
        perror("[client]Eroare la connect().\n");
        return 2;
    }
     ui->infoMessage->setStyleSheet("color:green;border:0px;");
    return 1;
}
void MainWindow::configureUi(){
    ui->portInput->setReadOnly(true);
    ui->portInput->setText("9000");
    ui->portInput->setFocusPolicy(Qt::NoFocus);
    ui->infoMessage->setText("");
    ui->infoMessage->setReadOnly(true);
    ui->infoMessage->setFocusPolicy(Qt::NoFocus);
    //  ui->ipAdressInput->setFocusPolicy(Qt::NoFocus);
    ui->pathOfFile->setReadOnly(true);
    ui->pathOfSaveFolder->setReadOnly(true);
    ui->convertFileBtn->setDisabled(true);
    ui->pathOfFile->setFocusPolicy(Qt::NoFocus);
    ui->pathOfSaveFolder->setFocusPolicy(Qt::NoFocus);
}
/**

*This function is called when the user attempts to close the application. It first closes the socket connection using the ::close() function.
*The function then accepts the event and allows the application to be closed.
*@param event A pointer to the QCloseEvent object.
*/
void MainWindow::closeEvent(QCloseEvent *event)
{

    ::close(sd);
    // accept event and close app.
    event->accept();
}


MainWindow::~MainWindow()
{
    delete ui;
}


