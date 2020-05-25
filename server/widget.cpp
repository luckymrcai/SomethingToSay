#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stopServiceBtn->setEnabled(false);
    DBUtil::getQSqlDatabase();


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_stopServiceBtn_clicked()
{
    ui->stopServiceBtn->setEnabled(false);
    ui->startServiceBtn->setEnabled(true);
    ui->status->setText("未开启服务");
    delete myServer;
}

void Widget::on_startServiceBtn_clicked()
{
    myServer=new MyTcpServer(this);
    myServer->listen(QHostAddress::Any,ui->port->text().toInt());
    ui->stopServiceBtn->setEnabled(true);
    ui->startServiceBtn->setEnabled(false);
    ui->status->setText("已开启服务");
    connect(myServer,&MyTcpServer::socketCountChange,this,&Widget::socketCountChangeSlot);
}

void Widget::socketCountChangeSlot(const qint32 socketCount)
{
    ui->onlineUserNum->display(socketCount);
}
