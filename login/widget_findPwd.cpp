#include "widget_findPwd.h"
#include "ui_widget_findPwd.h"

WidgetFindPwd::WidgetFindPwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFindPwd)
{
    ui->setupUi(this);
    connect(MySocket::getInstance(),SIGNAL(signal_findPwd(QJsonValue&)),this,SLOT(slot_findPwd(QJsonValue&)));

    //提示框
    messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("提示");
    messageBox->setWindowIcon(QIcon(":/images/img/2.ico"));
    messageBox->hide();
}

WidgetFindPwd::~WidgetFindPwd()
{
    delete ui;
}

void WidgetFindPwd::on_oKBtn_clicked()
{
    //装包
    QJsonObject json;
    json.insert("actionType","findPwd");
    QJsonObject data;
    data.insert("userAccount",ui->accountEdit->text());
    data.insert("securityQuestion",ui->comboBox->currentText());
    data.insert("securityAnswer",ui->qstionEdit->text());
    data.insert("userPwd",ui->pwdEdit->text());
    json.insert("data",QJsonValue(data));

    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf<<endl;
}

void WidgetFindPwd::on_BackBtn_clicked()
{
    this->hide();
    delete this;
}

void WidgetFindPwd::slot_findPwd(QJsonValue &value_data)
{
    QString result = value_data.toString();
    if(result == "success"){
        messageBox->setText("修改成功");
        messageBox->exec();
        this->hide();
        delete this;
    }else{
        messageBox->setText("账号或密保答案错误！");
        messageBox->exec();
    }
}
