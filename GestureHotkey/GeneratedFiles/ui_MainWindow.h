/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *infoLabel;
    QLabel *hotkey;
    QGridLayout *gridLayout_2;
    QPushButton *confirmButton;
    QTextEdit *commandEditor;
    QPushButton *cancelButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(542, 387);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        infoLabel = new QLabel(centralwidget);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei"));
        font.setPointSize(48);
        infoLabel->setFont(font);
        infoLabel->setStyleSheet(QStringLiteral("color: rgb(255, 170, 0);"));
        infoLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(infoLabel, 1, 0, 1, 1);

        hotkey = new QLabel(centralwidget);
        hotkey->setObjectName(QStringLiteral("hotkey"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(23);
        hotkey->setFont(font1);
        hotkey->setStyleSheet(QStringLiteral("color: rgb(47, 141, 255);"));
        hotkey->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(hotkey, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        confirmButton = new QPushButton(centralwidget);
        confirmButton->setObjectName(QStringLiteral("confirmButton"));

        gridLayout_2->addWidget(confirmButton, 1, 0, 1, 1);

        commandEditor = new QTextEdit(centralwidget);
        commandEditor->setObjectName(QStringLiteral("commandEditor"));

        gridLayout_2->addWidget(commandEditor, 0, 0, 1, 1);

        cancelButton = new QPushButton(centralwidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout_2->addWidget(cancelButton, 2, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 542, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(cancelButton, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(confirmButton, SIGNAL(clicked()), MainWindow, SLOT(setCommandDefinition()));
        QObject::connect(commandEditor, SIGNAL(textChanged()), MainWindow, SLOT(setCommandInfo()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        infoLabel->setText(QApplication::translate("MainWindow", "command", Q_NULLPTR));
        hotkey->setText(QApplication::translate("MainWindow", "Hotkey", Q_NULLPTR));
        confirmButton->setText(QApplication::translate("MainWindow", "Confirm", Q_NULLPTR));
        commandEditor->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">command</p></body></html>", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("MainWindow", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
