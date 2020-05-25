#include "widget_post.h"
#include "ui_widget_post.h"
#include <QDateTime>
WidgetPost::WidgetPost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetPost)
{
    ui->setupUi(this);
    ui->areaEdit->setText(User::getInstance()->getArea());
}

WidgetPost::~WidgetPost()
{
    delete ui;
}

void WidgetPost::on_backBtn_clicked()
{
    this->hide();
}

void WidgetPost::on_postBtn_clicked()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    //装包
    QJsonObject json;
    json.insert("actionType","post");
    QJsonObject data;
    data.insert("userId",User::getInstance()->getUserId());
    data.insert("content",ui->plainTextEdit->toPlainText());
    data.insert("createTime",current_date);
    data.insert("area",ui->areaEdit->text());
    json.insert("data",data);
    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf;
    ui->plainTextEdit->clear();
    this->hide();
}
