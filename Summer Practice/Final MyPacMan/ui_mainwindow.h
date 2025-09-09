/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAuthor;
    QAction *actionAbout;
    QAction *actionControls;
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *name;
    QPushButton *leaderboardButton;
    QHBoxLayout *horizontalLayout;
    QLabel *username;
    QLineEdit *enterName;
    QPushButton *startButton;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QMenu *menuInfo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 400);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow\n"
"{\n"
"    background-color: #2b2b2b;\n"
"    color: white;\n"
"}"));
        actionAuthor = new QAction(MainWindow);
        actionAuthor->setObjectName("actionAuthor");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionControls = new QAction(MainWindow);
        actionControls->setObjectName("actionControls");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(130, 0, 327, 321));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        name = new QLabel(widget);
        name->setObjectName("name");
        QFont font;
        font.setPointSize(40);
        name->setFont(font);
        name->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(name, 0, 0, 1, 1);

        leaderboardButton = new QPushButton(widget);
        leaderboardButton->setObjectName("leaderboardButton");
        QFont font1;
        font1.setPointSize(20);
        leaderboardButton->setFont(font1);

        gridLayout->addWidget(leaderboardButton, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        username = new QLabel(widget);
        username->setObjectName("username");
        QFont font2;
        font2.setPointSize(15);
        username->setFont(font2);

        horizontalLayout->addWidget(username);

        enterName = new QLineEdit(widget);
        enterName->setObjectName("enterName");
        enterName->setFont(font2);

        horizontalLayout->addWidget(enterName);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        startButton = new QPushButton(widget);
        startButton->setObjectName("startButton");
        startButton->setFont(font1);

        gridLayout->addWidget(startButton, 2, 0, 1, 1);

        exitButton = new QPushButton(widget);
        exitButton->setObjectName("exitButton");
        exitButton->setFont(font1);

        gridLayout->addWidget(exitButton, 4, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 25));
        menuInfo = new QMenu(menubar);
        menuInfo->setObjectName("menuInfo");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuInfo->menuAction());
        menuInfo->addAction(actionAuthor);
        menuInfo->addAction(actionControls);
        menuInfo->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MyPacMan", nullptr));
        actionAuthor->setText(QCoreApplication::translate("MainWindow", "Author", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionControls->setText(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        name->setText(QCoreApplication::translate("MainWindow", "MyPacMan", nullptr));
        leaderboardButton->setText(QCoreApplication::translate("MainWindow", "Leaderboard", nullptr));
        username->setText(QCoreApplication::translate("MainWindow", "Your name:", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("MainWindow", "Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
