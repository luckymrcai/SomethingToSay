#include "widget_set.h"

WidgetSet::WidgetSet(QWidget *parent) : QFrame(parent)
{
//    parentWidget = (WidgetMain *)parent;
//    QPalette pal;
    //this->setAutoFillBackground(true);
//    pal.setBrush(QPalette::Background,QBrush(Qt::white));
//    this->setPalette(pal);
    this->setStyleSheet("background-color:white;border:1px solid gray");

    userBtn = new QPushButton(this);
    userBtn->setGeometry(1,1,98,35);
    userBtn->setText("账号设置");
    userBtn->setStyleSheet("QPushButton{background-color:transparent;color:black;font-family:微软雅黑;border-width:0px}"
                           "QPushButton::hover{background-color:#f0f0f0;color:#EB7350;}");
    logoutBtn = new QPushButton(this);
    logoutBtn->setGeometry(1,35,98,35);
    logoutBtn->setText("注销");
    logoutBtn->setStyleSheet("QPushButton{background-color:transparent;color:black;font-family:微软雅黑;border-width:0px}"
                             "QPushButton::hover{background-color:#f0f0f0;color:#EB7350;}");
    quitBtn = new QPushButton(this);
    quitBtn->setGeometry(1,69,98,35);
    quitBtn->setText("退出");
    quitBtn->setStyleSheet("QPushButton{background-color:transparent;color:black;font-family:微软雅黑;border-width:0px}"
                           "QPushButton::hover{background-color:#f0f0f0;color:#EB7350;}");

    connect(userBtn,SIGNAL(clicked(bool)),this,SLOT(userBtn_clicked()));
    connect(logoutBtn,SIGNAL(clicked(bool)),this,SLOT(logoutBtn_clicked()));
    connect(quitBtn,SIGNAL(clicked(bool)),this,SLOT(quitBtn_clicked()));
}

void WidgetSet::userBtn_clicked()
{

}

void WidgetSet::logoutBtn_clicked()
{
    WidgetLogin::getInstance()->show();
    WidgetLogin::getInstance()->widgetMain->hide();
    WidgetLogin::getInstance()->widgetMain->widgetTop->setBtn->clicked();
}

void WidgetSet::quitBtn_clicked()
{
    exit(0);
}
