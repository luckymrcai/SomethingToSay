/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPlainTextEdit *logshow;
    QLabel *status;
    QLineEdit *port;
    QLabel *label_3;
    QLabel *label;
    QPushButton *startServiceBtn;
    QLabel *label_2;
    QPushButton *stopServiceBtn;
    QLCDNumber *onlineUserNum;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(400, 300);
        logshow = new QPlainTextEdit(Widget);
        logshow->setObjectName(QStringLiteral("logshow"));
        logshow->setGeometry(QRect(220, 20, 161, 151));
        status = new QLabel(Widget);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(100, 68, 81, 16));
        port = new QLineEdit(Widget);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(100, 19, 101, 20));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 120, 81, 16));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(21, 19, 48, 16));
        startServiceBtn = new QPushButton(Widget);
        startServiceBtn->setObjectName(QStringLiteral("startServiceBtn"));
        startServiceBtn->setGeometry(QRect(260, 200, 91, 41));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(21, 68, 60, 16));
        stopServiceBtn = new QPushButton(Widget);
        stopServiceBtn->setObjectName(QStringLiteral("stopServiceBtn"));
        stopServiceBtn->setGeometry(QRect(40, 200, 91, 41));
        onlineUserNum = new QLCDNumber(Widget);
        onlineUserNum->setObjectName(QStringLiteral("onlineUserNum"));
        onlineUserNum->setGeometry(QRect(100, 110, 101, 41));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        status->setText(QApplication::translate("Widget", "\346\234\252\345\274\200\345\220\257\346\234\215\345\212\241", Q_NULLPTR));
        port->setText(QApplication::translate("Widget", "9999", Q_NULLPTR));
        label_3->setText(QApplication::translate("Widget", "\345\234\250\347\272\277\347\224\250\346\210\267\346\225\260\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267\357\274\232", Q_NULLPTR));
        startServiceBtn->setText(QApplication::translate("Widget", "\345\274\200\345\220\257\346\234\215\345\212\241", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\346\234\215\345\212\241\347\212\266\346\200\201\357\274\232", Q_NULLPTR));
        stopServiceBtn->setText(QApplication::translate("Widget", "\345\201\234\346\255\242\346\234\215\345\212\241", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
