/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_3;
    QComboBox *selectTypeBox;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *pathOfSaveFolder;
    QPushButton *selectFolderButton;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *convertFileBtn;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *ipAdressInput;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLineEdit *portInput;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *infoMessage;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *pathOfFile;
    QPushButton *selectFileButton;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 370);
        MainWindow->setMinimumSize(QSize(600, 370));
        MainWindow->setMaximumSize(QSize(600, 370));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(600, 370));
        centralwidget->setMaximumSize(QSize(535, 370));
        centralwidget->setStyleSheet(QString::fromUtf8("background-color:#4C0070;"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        verticalSpacer_5 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_5, 8, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_8 = new QSpacerItem(16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("\n"
"    font: bold 14px;\n"
"    min-height:20px;\n"
"	max-width:50px;\n"
"    padding:3px;\n"
"	\n"
"qproperty-alignment: AlignCenter;"));

        horizontalLayout_5->addWidget(label_3);

        selectTypeBox = new QComboBox(centralwidget);
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->addItem(QString());
        selectTypeBox->setObjectName("selectTypeBox");

        horizontalLayout_5->addWidget(selectTypeBox);

        horizontalSpacer_7 = new QSpacerItem(500, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        gridLayout_2->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 11, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_6, 4, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pathOfSaveFolder = new QLineEdit(centralwidget);
        pathOfSaveFolder->setObjectName("pathOfSaveFolder");
        pathOfSaveFolder->setStyleSheet(QString::fromUtf8("	QLineEdit\n"
"{border-style:solid;\n"
"	border-width: 3px;\n"
"    border-radius: 10px;\n"
"    border-color: rgb(45, 0, 71);\n"
"    font: bold 12px;\n"
"    min-height:20px;\n"
"	max-width:400px;\n"
"    padding:3px;\n"
"	background-color: rgb(79, 3, 121);\n"
"qproperty-alignment: AlignCenter;}\n"
""));

        horizontalLayout_4->addWidget(pathOfSaveFolder);

        selectFolderButton = new QPushButton(centralwidget);
        selectFolderButton->setObjectName("selectFolderButton");
        selectFolderButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton\n"
"{ font: bold 14px;\n"
"background-color:rgb(79, 3, 121);\n"
"max-width:100px;\n"
"min-height:20px;\n"
"\n"
"}\n"
"QPushButton:hover\n"
"{ font: bold 14px;\n"
"background-color:rgb(133, 3, 205)\n"
"}"));

        horizontalLayout_4->addWidget(selectFolderButton);


        gridLayout_2->addLayout(horizontalLayout_4, 7, 0, 1, 1);

        verticalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_7, 10, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_9 = new QSpacerItem(248, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);

        convertFileBtn = new QPushButton(centralwidget);
        convertFileBtn->setObjectName("convertFileBtn");
        convertFileBtn->setMinimumSize(QSize(80, 40));
        convertFileBtn->setMaximumSize(QSize(80, 40));
        convertFileBtn->setStyleSheet(QString::fromUtf8("\n"
"QPushButton\n"
"{ font: bold 14px;\n"
"background-color:rgb(79, 3, 121)\n"
"}\n"
"QPushButton:hover\n"
"{ font: bold 14px;\n"
"background-color:rgb(133, 3, 205)\n"
"}"));

        horizontalLayout_6->addWidget(convertFileBtn);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);


        gridLayout_2->addLayout(horizontalLayout_6, 9, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");

        verticalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(86, 16777215));
        label->setStyleSheet(QString::fromUtf8(" font: bold 14px;\n"
"    min-height:20px;\n"
"	max-width:80px;\n"
"    padding:3px;\n"
"\n"
"qproperty-alignment: AlignCenter;"));

        horizontalLayout->addWidget(label);

        ipAdressInput = new QLineEdit(centralwidget);
        ipAdressInput->setObjectName("ipAdressInput");
        ipAdressInput->setMinimumSize(QSize(160, 32));
        ipAdressInput->setMaximumSize(QSize(122, 16777215));
        ipAdressInput->setStyleSheet(QString::fromUtf8("	QLineEdit\n"
"{border-style:solid;\n"
"	border-width: 3px;\n"
"    border-radius: 10px;\n"
"    border-color: rgb(45, 0, 71);\n"
"    font: bold 16px;\n"
"    min-height:20px;\n"
"	max-width:110px;\n"
"    padding:3px;\n"
"	background-color: rgb(79, 3, 121);\n"
"qproperty-alignment: AlignCenter;}\n"
"QLineEdit:hover\n"
"{\n"
"    border-color: white;\n"
"}\n"
"QLineEdit:focus{\n"
"background-color:rgb(133, 3, 205);}"));

        horizontalLayout->addWidget(ipAdressInput);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(46, 16777215));
        label_2->setStyleSheet(QString::fromUtf8("\n"
"    font: bold 14px;\n"
"    min-height:20px;\n"
"	max-width:40px;\n"
"    padding:3px;\n"
"qproperty-alignment: AlignCenter;"));

        horizontalLayout->addWidget(label_2);

        portInput = new QLineEdit(centralwidget);
        portInput->setObjectName("portInput");
        portInput->setStyleSheet(QString::fromUtf8("QLineEdit{	border-style:solid;\n"
"	border-width: 3px;\n"
"    border-radius: 10px;\n"
"    border-color: rgb(45, 0, 71);\n"
"    font: bold 16px;\n"
"    min-height:20px;\n"
"	max-width:50px;\n"
"    padding:3px;\n"
"	background-color: rgb(79, 3, 121);\n"
"qproperty-alignment: AlignCenter;}\n"
"QLineEdit:hover\n"
"{\n"
"    border-color: white;\n"
"}\n"
"QLineEdit:focus{\n"
"background-color:rgb(133, 3, 205);}"));

        horizontalLayout->addWidget(portInput);

        horizontalSpacer_3 = new QSpacerItem(100, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_5->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 11, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        verticalSpacer_3 = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        infoMessage = new QLineEdit(centralwidget);
        infoMessage->setObjectName("infoMessage");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infoMessage->sizePolicy().hasHeightForWidth());
        infoMessage->setSizePolicy(sizePolicy);
        infoMessage->setMinimumSize(QSize(177, 0));
        infoMessage->setMaximumSize(QSize(300, 16777215));
        infoMessage->setBaseSize(QSize(110, 0));
        infoMessage->setStyleSheet(QString::fromUtf8("border:0px;\n"
"qproperty-alignment: AlignCenter;"));

        horizontalLayout_3->addWidget(infoMessage);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout_5);


        gridLayout_2->addLayout(verticalLayout_3, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pathOfFile = new QLineEdit(centralwidget);
        pathOfFile->setObjectName("pathOfFile");
        pathOfFile->setStyleSheet(QString::fromUtf8("	QLineEdit\n"
"{border-style:solid;\n"
"	border-width: 3px;\n"
"    border-radius: 10px;\n"
"    border-color: rgb(45, 0, 71);\n"
"    font: bold 12px;\n"
"    min-height:20px;\n"
"	max-width:400px;\n"
"    padding:3px;\n"
"	background-color: rgb(79, 3, 121);\n"
"qproperty-alignment: AlignCenter;}\n"
""));

        horizontalLayout_2->addWidget(pathOfFile);

        selectFileButton = new QPushButton(centralwidget);
        selectFileButton->setObjectName("selectFileButton");
        selectFileButton->setStyleSheet(QString::fromUtf8("\n"
"QPushButton\n"
"{ font: bold 14px;\n"
"background-color:rgb(79, 3, 121);\n"
"max-width:100px;\n"
"min-height:20px;\n"
"\n"
"}\n"
"QPushButton:hover\n"
"{ font: bold 14px;\n"
"background-color:rgb(133, 3, 205)\n"
"}"));

        horizontalLayout_2->addWidget(selectFileButton);


        gridLayout_2->addLayout(horizontalLayout_2, 5, 0, 1, 1);

        verticalSpacer_8 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_8, 6, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_4, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        selectTypeBox->setItemText(0, QCoreApplication::translate("MainWindow", "asp-php", nullptr));
        selectTypeBox->setItemText(1, QCoreApplication::translate("MainWindow", "avi-flv", nullptr));
        selectTypeBox->setItemText(2, QCoreApplication::translate("MainWindow", "avi-gif", nullptr));
        selectTypeBox->setItemText(3, QCoreApplication::translate("MainWindow", "avi-mp4", nullptr));
        selectTypeBox->setItemText(4, QCoreApplication::translate("MainWindow", "bmp-gif", nullptr));
        selectTypeBox->setItemText(5, QCoreApplication::translate("MainWindow", "bmp-jpg", nullptr));
        selectTypeBox->setItemText(6, QCoreApplication::translate("MainWindow", "bmp-png", nullptr));
        selectTypeBox->setItemText(7, QCoreApplication::translate("MainWindow", "gif-avi", nullptr));
        selectTypeBox->setItemText(8, QCoreApplication::translate("MainWindow", "gif-flv", nullptr));
        selectTypeBox->setItemText(9, QCoreApplication::translate("MainWindow", "gif-mp4", nullptr));
        selectTypeBox->setItemText(10, QCoreApplication::translate("MainWindow", "jpg-bmp", nullptr));
        selectTypeBox->setItemText(11, QCoreApplication::translate("MainWindow", "jpg-gif", nullptr));
        selectTypeBox->setItemText(12, QCoreApplication::translate("MainWindow", "jpg-png", nullptr));
        selectTypeBox->setItemText(13, QCoreApplication::translate("MainWindow", "mp4-flv", nullptr));
        selectTypeBox->setItemText(14, QCoreApplication::translate("MainWindow", "mp4-gif", nullptr));
        selectTypeBox->setItemText(15, QCoreApplication::translate("MainWindow", "pdf-html", nullptr));
        selectTypeBox->setItemText(16, QCoreApplication::translate("MainWindow", "pdf-ps", nullptr));
        selectTypeBox->setItemText(17, QCoreApplication::translate("MainWindow", "pdf-txt", nullptr));
        selectTypeBox->setItemText(18, QCoreApplication::translate("MainWindow", "png-bmp", nullptr));
        selectTypeBox->setItemText(19, QCoreApplication::translate("MainWindow", "png-gif", nullptr));
        selectTypeBox->setItemText(20, QCoreApplication::translate("MainWindow", "png-jpg", nullptr));
        selectTypeBox->setItemText(21, QCoreApplication::translate("MainWindow", "ps-ascii", nullptr));
        selectTypeBox->setItemText(22, QCoreApplication::translate("MainWindow", "ps-pdf", nullptr));
        selectTypeBox->setItemText(23, QCoreApplication::translate("MainWindow", "tex-html", nullptr));

        selectTypeBox->setPlaceholderText(QString());
        pathOfSaveFolder->setPlaceholderText(QCoreApplication::translate("MainWindow", "Path of the folder where the converted file will be saved", nullptr));
        selectFolderButton->setText(QCoreApplication::translate("MainWindow", "Select folder", nullptr));
        convertFileBtn->setText(QCoreApplication::translate("MainWindow", "Convert", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP Adress:", nullptr));
        ipAdressInput->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        portInput->setText(QCoreApplication::translate("MainWindow", "9000", nullptr));
        infoMessage->setText(QCoreApplication::translate("MainWindow", "CAN'T CONNECT TO SERVER", nullptr));
        pathOfFile->setPlaceholderText(QCoreApplication::translate("MainWindow", "Path of the file you wish to convert", nullptr));
        selectFileButton->setText(QCoreApplication::translate("MainWindow", "Select file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
