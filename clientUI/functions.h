#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "qcombobox.h"
#include "qlineedit.h"
#include "qpushbutton.h"

void verifyIfValid(QLineEdit* pathOfFile, QLineEdit* pathOfSaveFolder, QPushButton* convertFileBtn, QComboBox* selectTypeBox);
void connectSignalsFile(QLineEdit* pathOfFile, QLineEdit* pathOfSaveFolder, QPushButton* convertFileBtn, QComboBox* selectTypeBox );

void extractFileHash(char* fileHash);
void getFileHash(char* fileName,char * fileHash);
void sendFileHash(int sd,char* fileName);

void sendType(int sd,char *fileTypes);


#endif // FUNCTIONS_H
