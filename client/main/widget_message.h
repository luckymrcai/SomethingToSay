#ifndef WIDGET_MESSAGE_H
#define WIDGET_MESSAGE_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QBrush>
#include <QMessageBox>
#include <QDateTime>
#include "public.h"
#include "mysocket.h"
#include "user.h"
#include "widget_comment.h"

namespace Ui {
class WidgetMessage;
}

class WidgetMessage : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetMessage(QWidget *parent = 0);
    ~WidgetMessage();
    QWidget *hLineWidget1;
    QWidget *hLineWidget2;
    QWidget *vLineWidget1;
    QWidget *vLineWidget2;
    QWidget *vLineWidget3;
    MSG_T msg;


    int message_width = 610;//消息的宽度
    int message_height = 400;//消息的高度
    void setMyStytle();
signals:

    void signal_forward_ok();
private slots:
    void on_collectBtn_clicked();

    void on_forwardBtn_clicked();

    void on_commentBtn_clicked();

    void on_likeBtn_clicked();

    void slot_collect(QJsonValue &value_data);
    void slot_forward(QJsonValue &value_data);
    void slot_comment(QJsonValue &value_data);
    void slot_like(QJsonValue &value_data);
private:
    Ui::WidgetMessage *ui;


};

#endif // WIDGET_MESSAGE_H
