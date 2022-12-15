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
int sd; // descriptorul de socket
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocus();
    configureUi();
    connectFileDialogsToBtn();
    //QObject::connect(ui->connectBtn, &QPushButton::clicked,this,&MainWindow::connectToServer);
    connectSignalsFile(ui->pathOfFile,ui->pathOfSaveFolder,ui->convertFileBtn,ui->selectTypeBox);
    QObject::connect(ui->convertFileBtn, &QPushButton::clicked,this,&MainWindow::sendFileInfo);
}
void MainWindow::connectFileDialogsToBtn(){

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
void MainWindow::sendFileInfo()//FILE *fp, int sd,long int size
{
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
                perror("[client]Error in opening fileName file");
                exit(1);
            }


        sendType(sd,conversionType);
      //  sleep(5);

        sendFileHash(sd,filePath);
        sizeOfFile= ::sendFileSize(fp,sd);

       // sleep(5);

        ::sendFile(fp, sd, sizeOfFile);
       // sleep(10);
        ::extractTypes(conversionType,fileType1,fileType2);
       //::writeReceivedFile(sd,savePath,filePath,fileType2,fileNr);
   ::close(sd);
        ui->infoMessage->setText("FILE WAS SUCCESSFULY CONVERTED");
}
int MainWindow::connectToServer(){

    QLineEdit *portInput = ui->portInput;


    struct sockaddr_in server; // structura folosita pentru conectare
    // mesajul trimis
    /* stabilim portul */
    port = portInput->text().toInt();

    /* cream socketul */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Eroare la socket().\n");
        return 2;
    }

    /* umplem structura folosita pentru realizarea conexiunii cu serverul */
    /* familia socket-ului */
    server.sin_family = AF_INET;
    /* adresa IP a serverului */
    server.sin_addr.s_addr = inet_addr(ui->ipAdressInput->text().toUtf8().data());
    /* portul de conectare */
    server.sin_port = htons(port);

    if (::connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
        ui->infoMessage->setText("CAN'T CONNECT TO SERVER");
        ui->infoMessage->setStyleSheet("color:red;border:0px;");
        perror("[client]Eroare la connect().\n");
        return 2;
    }

    ui->infoMessage->setText("PLEASE WAIT FOR YOUR FILE TO BE CONVERTED");
    ui->infoMessage->setStyleSheet("color:green;border:0px;");
   // ui->connectBtn->setDisabled(true);
    ui->selectFileButton->setDisabled(false);
    ui->selectFolderButton->setDisabled(false);
    ui->selectTypeBox->setDisabled(false);

    return 1;
}
void MainWindow::configureUi(){
    ui->portInput->setReadOnly(true);
    ui->portInput->setText("9000");
    ui->portInput->setFocusPolicy(Qt::NoFocus);
    ui->infoMessage->setText("");
    ui->infoMessage->setReadOnly(true);
    ui->infoMessage->setFocusPolicy(Qt::NoFocus);
    ui->ipAdressInput->setFocusPolicy(Qt::NoFocus);
    ui->pathOfFile->setReadOnly(true);
    ui->pathOfSaveFolder->setReadOnly(true);
    ui->convertFileBtn->setDisabled(true);
    ui->pathOfFile->setFocusPolicy(Qt::NoFocus);
    ui->pathOfSaveFolder->setFocusPolicy(Qt::NoFocus);
}
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


