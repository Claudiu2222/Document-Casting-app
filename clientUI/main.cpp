#include "mainwindow.h"
#include<unistd.h>
#include <QApplication>
/**
 * The main entry point of the CastDoc application. Initializes the QApplication and MainWindow, sets the window title, and shows the main window.
 * 
 * @param argc The number of command-line arguments passed to the program.
 * @param argv An array of pointers to the command-line arguments passed to the program.
 * @return The exit code of the application.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("CastDoc");
    w.show();

   //w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    return a.exec();
}
