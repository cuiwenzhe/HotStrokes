/********************************************************************************
** Form generated from reading UI file 'GestureHotkey.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GESTUREHOTKEY_H
#define UI_GESTUREHOTKEY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GestureHotkeyClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QLabel *textLabel;
    QLabel *hotkeyLabel;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GestureHotkeyClass)
    {
        if (GestureHotkeyClass->objectName().isEmpty())
            GestureHotkeyClass->setObjectName(QStringLiteral("GestureHotkeyClass"));
        GestureHotkeyClass->resize(1000, 900);
        GestureHotkeyClass->setMinimumSize(QSize(1000, 900));
        GestureHotkeyClass->setMaximumSize(QSize(1000, 900));
        GestureHotkeyClass->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        centralWidget = new QWidget(GestureHotkeyClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setStyleSheet(QStringLiteral("border-color: rgba(255, 255, 255, 0);"));
        graphicsView->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(graphicsView);

        textLabel = new QLabel(centralWidget);
        textLabel->setObjectName(QStringLiteral("textLabel"));
        textLabel->setMinimumSize(QSize(0, 100));
        textLabel->setMaximumSize(QSize(16777215, 300));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei UI"));
        font.setPointSize(90);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        textLabel->setFont(font);
        textLabel->setStyleSheet(QStringLiteral("color: rgb(255, 170, 0);"));
        textLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(textLabel);

        hotkeyLabel = new QLabel(centralWidget);
        hotkeyLabel->setObjectName(QStringLiteral("hotkeyLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(30);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        hotkeyLabel->setFont(font1);
        hotkeyLabel->setStyleSheet(QStringLiteral("color: rgb(70, 135, 255);"));
        hotkeyLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(hotkeyLabel);

        GestureHotkeyClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GestureHotkeyClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        GestureHotkeyClass->setStatusBar(statusBar);

        retranslateUi(GestureHotkeyClass);

        QMetaObject::connectSlotsByName(GestureHotkeyClass);
    } // setupUi

    void retranslateUi(QMainWindow *GestureHotkeyClass)
    {
        GestureHotkeyClass->setWindowTitle(QApplication::translate("GestureHotkeyClass", "GestureHotkey", Q_NULLPTR));
        textLabel->setText(QString());
        hotkeyLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GestureHotkeyClass: public Ui_GestureHotkeyClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GESTUREHOTKEY_H
