#ifndef WIDGET_TOP_H
#define WIDGET_TOP_H

#include <QWidget>
#include <QPushButton>
#include "user.h"

class WidgetMainTop :public QWidget
{
    Q_OBJECT
public:
    WidgetMainTop(QWidget *parent = 0);
    ~WidgetMainTop();

    QPushButton *refreshBtn;
    QPushButton *nameBtn;
    QPushButton *setBtn;
    QPushButton *postBtn;

};

#endif // WIDGET_TOP_H
