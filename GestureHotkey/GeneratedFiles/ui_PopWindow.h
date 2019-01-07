/********************************************************************************
** Form generated from reading UI file 'PopWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPWINDOW_H
#define UI_POPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;

    void setupUi(QMainWindow *PopWindow)
    {
        if (PopWindow->objectName().isEmpty())
            PopWindow->setObjectName(QStringLiteral("PopWindow"));
        PopWindow->resize(882, 613);
        centralwidget = new QWidget(PopWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 60, 741, 481));
        QFont font;
        font.setPointSize(60);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(4, 215, 57);"));
        PopWindow->setCentralWidget(centralwidget);

        retranslateUi(PopWindow);

        QMetaObject::connectSlotsByName(PopWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PopWindow)
    {
        PopWindow->setWindowTitle(QApplication::translate("PopWindow", "PopWindow", Q_NULLPTR));
        label->setText(QApplication::translate("PopWindow", "THE BOMB WAS\n"
" TERMINATED", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PopWindow: public Ui_PopWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPWINDOW_H
