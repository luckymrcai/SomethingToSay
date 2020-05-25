#ifndef WIDGET_SET_H
#define WIDGET_SET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include "login/widget_login.h"

class WidgetMain;
class WidgetSet : public QFrame
{
    Q_OBJECT
public:
    explicit WidgetSet(QWidget *parent = 0);
    QPushButton *userBtn;
    QPushButton *logoutBtn;
    QPushButton *quitBtn;

signals:

public slots:
    void userBtn_clicked();
    void logoutBtn_clicked();
    void quitBtn_clicked();
};

#endif // WIDGET_SET_H
