#ifndef WIDGET_FINDPWD_H
#define WIDGET_FINDPWD_H

#include <QWidget>
#include <QMessageBox>
#include "mysocket.h"

namespace Ui {
class WidgetFindPwd;
}

class WidgetFindPwd : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetFindPwd(QWidget *parent = 0);
    ~WidgetFindPwd();

    QMessageBox *messageBox;
private slots:
    void on_oKBtn_clicked();

    void on_BackBtn_clicked();

    void slot_findPwd(QJsonValue &value_data);
private:
    Ui::WidgetFindPwd *ui;
};

#endif // WIDGET_FINDPWD_H
