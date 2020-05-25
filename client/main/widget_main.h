#ifndef WIDGET_MAIN_H
#define WIDGET_MAIN_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QList>
#include <QPushButton>
#include <QMessageBox>
#include "mysocket.h"
#include "widget_post.h"
#include "widget_message.h"
#include "widget_mainTop.h"
#include "widget_set.h"


class WidgetSet;
class WidgetMain : public QWidget
{
    Q_OBJECT

public:
    WidgetMain(QWidget *parent = 0);
    ~WidgetMain();
    QScrollArea *scrollArea;//滚动区
    QWidget *scrollWidget;//滚动区界面
    WidgetMainTop *widgetTop;//上部分界面
    WidgetPost *widgetPost;//发布界面
    WidgetSet *widgetSet;//设置界面
    QMessageBox *messageBox;//提示框
    QPushButton *lookMoreBtn;//按钮_查看更多

    int WINDOWS_WIDTH = 650;//窗口宽度
    int WINDOWS_HEIGHT = 810;//窗口长度
    int message_x = 10;//消息的x轴坐标
    int message_y = 80;//消息的y轴坐标
    int message_space = 20;//消息的上下间距

    QList<WidgetMessage *>list_msg;

public slots:
    void refreshBtn_clicked();//按钮_刷新
    void lookMoreBtn_clicked();//按钮_查看更多
    void postBtn_clicked();//按钮_发布
    void setBtn_clicked();//按钮_设置
    void nameBtn_clicked();//按钮_用户名

    void slot_scroolWidget(int value);
    void slot_refresh(QJsonValue &value_data);
    void slot_readMore(QJsonValue &value_data);
    void slot_post(QJsonValue &value_data);
    void slot_forward_ok();
private:


};

#endif // WIDGET_MAIN_H
