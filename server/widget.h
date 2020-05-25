#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dbutil.h"
#include "mytcpserver.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    MyTcpServer *myServer;
    ~Widget();


private slots:

    void on_stopServiceBtn_clicked();

    void on_startServiceBtn_clicked();

    void socketCountChangeSlot(const qint32 socketCount);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
