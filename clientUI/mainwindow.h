#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<arpa/inet.h>
#include <sys/socket.h>
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

   void connectFileDialogsToBtn();
   int connectToServer();
   void configureUi();

   void closeEvent(QCloseEvent *event);
   void sendFileInfo();//FILE *fp, int sd, char* fileName
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

