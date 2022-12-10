#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocus();
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_2->setText("9000");
    ui->lineEdit_3->setText("");
    ui->pathOfFile->setReadOnly(true);
    ui->pathOfSaveFolder->setReadOnly(true);
    ui->pathOfFile->setFocusPolicy(Qt::NoFocus);
    ui->pathOfSaveFolder->setFocusPolicy(Qt::NoFocus);
    connectFileDialogsToBtn();


}
void MainWindow::connectFileDialogsToBtn(){
    QPushButton *buttonFile=ui->selectFileButton;
    QLineEdit *lineEditPathFile = ui->pathOfFile;
    QPushButton *buttonFolder=ui->selectFolderButton;
    QLineEdit *lineEditPathFolder = ui->pathOfSaveFolder;
    QObject::connect(buttonFile, &QPushButton::clicked, [lineEditPathFile]() {
        // Show the file dialog and get the selected file
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Select File", "", "Files (*.*)");

        // Set the text of the line edit to the selected file's path
        lineEditPathFile->setText(fileName);
    });
    QObject::connect(buttonFolder, &QPushButton::clicked, [lineEditPathFolder]() {
        // Show the file dialog and get the selected file
        QString fileName = QFileDialog::getExistingDirectory(nullptr, "Select Folder", "", QFileDialog::ShowDirsOnly);

        // Set the text of the line edit to the selected file's path
        lineEditPathFolder->setText(fileName);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


