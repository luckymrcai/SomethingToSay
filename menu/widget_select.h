#ifndef WIDGET_SELECT_H
#define WIDGET_SELECT_H

#include <QWidget>
#include "main/widget_main.h"
#include "db/dbutil.h"

namespace Ui {
class WidgetSelect;
}

class WidgetMain;
class WidgetSelect : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSelect(QWidget *parent = 0);
    ~WidgetSelect();
    WidgetMain *widget_main;
private:
    Ui::WidgetSelect *ui;

private slots:

    void on_HappyBtn_clicked();

    void on_SadBtn_clicked();

};

#endif // WIDGET_SELECT_H
