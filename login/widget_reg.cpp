#include "widget_reg.h"
#include "ui_widget_reg.h"

WidgetReg::WidgetReg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetReg)
{
    ui->setupUi(this);
    connect(MySocket::getInstance(),SIGNAL(signal_reg(QJsonValue&)),this,SLOT(slot_reg(QJsonValue&)));

    //提示框
    messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("提示");
    messageBox->setWindowIcon(QIcon(":/images/img/2.ico"));
    messageBox->hide();
}

WidgetReg::~WidgetReg()
{
//    qDebug()<<"~WidgetReg()";
    delete ui;
}

void WidgetReg::on_oKBtn_clicked()
{
    //装包
    QJsonObject json;
    json.insert("actionType","reg");
    QJsonObject data;
    data.insert("userAccount",ui->accountEdit->text());
    data.insert("userPwd",ui->pwdEdit->text());
    data.insert("securityQuestion",ui->comboBox->currentText());
    data.insert("securityAnswer",ui->qstionEdit->text());
    json.insert("data",QJsonValue(data));
    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf<<endl;
}

void WidgetReg::on_BackBtn_clicked()
{
    this->hide();
    delete this;
}

void WidgetReg::slot_reg(QJsonValue &value_data)
{
    QString result = value_data.toString();
    if(result == "success"){
        messageBox->setText("注册成功！");
        messageBox->exec();
        this->hide();
        delete this;
    }else{
        messageBox->setText("该帐号已被注册！");
        messageBox->exec();
    }
}
