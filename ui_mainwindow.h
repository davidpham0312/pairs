/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *start_button;
    QTextBrowser *text_browser;
    QLineEdit *player1;
    QLineEdit *player2;
    QLineEdit *card_number;
    QPushButton *quit_button;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(569, 306);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 191, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 70, 191, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 130, 191, 21));
        start_button = new QPushButton(centralwidget);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setGeometry(QRect(390, 20, 161, 131));
        QFont font;
        font.setPointSize(40);
        start_button->setFont(font);
        start_button->setStyleSheet(QString::fromUtf8("background-color: rgb(27, 255, 0);\n"
"border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        text_browser = new QTextBrowser(centralwidget);
        text_browser->setObjectName(QString::fromUtf8("text_browser"));
        text_browser->setGeometry(QRect(20, 190, 341, 61));
        player1 = new QLineEdit(centralwidget);
        player1->setObjectName(QString::fromUtf8("player1"));
        player1->setGeometry(QRect(250, 20, 113, 24));
        player2 = new QLineEdit(centralwidget);
        player2->setObjectName(QString::fromUtf8("player2"));
        player2->setGeometry(QRect(250, 70, 113, 24));
        card_number = new QLineEdit(centralwidget);
        card_number->setObjectName(QString::fromUtf8("card_number"));
        card_number->setGeometry(QRect(250, 130, 113, 24));
        quit_button = new QPushButton(centralwidget);
        quit_button->setObjectName(QString::fromUtf8("quit_button"));
        quit_button->setGeometry(QRect(390, 190, 161, 61));
        quit_button->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 16, 0);\n"
"border-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 0, 0, 0), stop:0.52 rgba(0, 0, 0, 0), stop:0.565 rgba(82, 121, 76, 33), stop:0.65 rgba(159, 235, 148, 64), stop:0.721925 rgba(255, 238, 150, 129), stop:0.77 rgba(255, 128, 128, 204), stop:0.89 rgba(191, 128, 255, 64), stop:1 rgba(0, 0, 0, 0));"));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(quit_button, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Enter Player 1 name:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Enter Player 2 name:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Enter total number of cards:", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        quit_button->setText(QCoreApplication::translate("MainWindow", "Quit Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
