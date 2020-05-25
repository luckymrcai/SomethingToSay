#ifndef WIDGET_LOGIN_H
#define WIDGET_LOGIN_H

#include <QWidget>
#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include <QMessageBox>
#include "menu/widget_select.h"
#include "db/dbutil.h"
#include "login/widget_findPwd.h"
#include "login/widget_reg.h"
#include "mysocket.h"
#include "main/widget_main.h"


class WidgetMain;
namespace Ui {
class WidgetLogin;
}

class WidgetLogin : public QWidget
{
    Q_OBJECT

public:
    static WidgetLogin *getInstance(){
        if(widgetLogin == nullptr){
            widgetLogin = new WidgetLogin;
        }
        return widgetLogin;
    }
//    WidgetSelect *widgetSelect;
    QMessageBox *messageBox;
    WidgetMain *widgetMain;

private:
    WidgetLogin(QWidget *parent = 0);
    static WidgetLogin *widgetLogin;

private slots:


    void on_regBtn_clicked();

    void on_findPwdBtn_clicked();

    void on_loginBtn_clicked();

    void slot_login(QJsonValue &value_data);
private:
    Ui::WidgetLogin *ui;
};

#endif // WIDGET_LOGIN_H
