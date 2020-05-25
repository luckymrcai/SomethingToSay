#ifndef WIDGET_REG_H
#define WIDGET_REG_H

#include <QWidget>
#include <QMessageBox>
#include "mysocket.h"

namespace Ui {
class WidgetReg;
}

class WidgetReg : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetReg(QWidget *parent = 0);
    ~WidgetReg();
    QMessageBox *messageBox;
private slots:
    void on_oKBtn_clicked();

    void on_BackBtn_clicked();

    void slot_reg(QJsonValue &value_data);
private:
    Ui::WidgetReg *ui;
};

#endif // WIDGET_REG_H
