#include "mainwindow.h"
#include<unistd.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

   //w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    return a.exec();
}
