#ifndef WIDGET_COMMENT_H
#define WIDGET_COMMENT_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QTextEdit>
#include <QPalette>
#include "widget_message.h"
#include "widget_userComment.h"
#include "public.h"
class WidgetMessage;

class WidgetComment : public QWidget
{
    Q_OBJECT
public:
    WidgetComment(WidgetMessage *widgetMessage_1,QWidget *parent = 0);
    QScrollArea *scrollArea;//滚动区
    QWidget *scrollWidget;//滚动区界面
    WidgetMessage *widgetMessage;//上部分界面-消息框
    QWidget *widget_bottom;//下部分界面
    QPushButton *headPortraitBtn;//按钮_头像
    QPushButton *commentBtn;//按钮_评论
    QTextEdit *textEdit;//编辑框_评论内容
    MSG_T msg;
    int y = 0;
    void request_comment_bag();

    QList<WidgetUserComment *>list_com;
signals:

public slots:
    void commentBtn_clicked();
    void slot_comment(QJsonValue &value_data);
    void slot_postComment(QJsonValue &value_data);

};

#endif // WIDGET_COMMENT_H
