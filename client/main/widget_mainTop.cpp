#include "widget_mainTop.h"

WidgetMainTop::WidgetMainTop(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(629,50);
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(Qt::white));
    this->setPalette(pal);

    refreshBtn = new QPushButton(this);
    refreshBtn->setGeometry(5,5,40,40);
    refreshBtn->setStyleSheet("QPushButton{border-image:url(:/images/img/ICON/refresh1.jpg)}"
                              "QPushButton::hover{border-image:url(:/images/img/ICON/refresh1_hover.jpg)}"
                              "QPushButton::pressed{border-image:url(:/images/img/ICON/refresh1_press.jpg)}");
    refreshBtn->setCursor(QCursor(Qt::PointingHandCursor));//变成手势
    //按钮_用户名
    nameBtn = new QPushButton(this);
    nameBtn->setGeometry(230,5,160,40);
    nameBtn->setIcon(QIcon(":/images/img/ICON/friend01.png"));
    nameBtn->setText(User::getInstance()->getUserName());
    nameBtn->setCursor(QCursor(Qt::PointingHandCursor));//变成手势
    nameBtn->setStyleSheet("QPushButton{background:transparent;font-family:微软雅黑}"
                           "QPushButton::hover{color:#EB7350;}");
    //按钮_设置
    setBtn = new QPushButton(this);
    setBtn->setGeometry(550,10,30,30);
    setBtn->setStyleSheet("QPushButton{border-image:url(:/images/img/ICON/setting_01.png)}"
                          "QPushButton::hover{border-image:url(:/images/img/ICON/setting_02.png)}");
    setBtn->setCursor(QCursor(Qt::PointingHandCursor));//变成手势
    //按钮_发布
    postBtn = new QPushButton(this);
    postBtn->setGeometry(590,10,30,30);
    postBtn->setStyleSheet("QPushButton{border-image:url(:/images/img/ICON/write.jpg)}");
    postBtn->setCursor(QCursor(Qt::PointingHandCursor));//变成手势
    //横线_橙色
    QWidget *line1 = new QWidget(this);
    line1->setGeometry(0,0,this->width(),2);
    line1->setAutoFillBackground(true);
    pal.setBrush(QPalette::Background,QBrush("#FA7D3C"));
    line1->setPalette(pal);
    //横线_灰色
    QWidget *line2 = new QWidget(this);
    line2->setGeometry(0,this->height()-2,this->width(),1);
    line2->setAutoFillBackground(true);
    pal.setBrush(QPalette::Background,QBrush(Qt::gray));
    line2->setPalette(pal);


}

WidgetMainTop::~WidgetMainTop()
{
    delete this;
}




