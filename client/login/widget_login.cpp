#include "widget_login.h"
#include "ui_widget_login.h"

WidgetLogin *WidgetLogin::widgetLogin = 0;


WidgetLogin::WidgetLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetLogin)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/img/2.ico"));

    //设置背景
    QPixmap pixmap(":/images/img/background.jpg");
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(pixmap.scaled(ui->widget->size())));
    ui->widget->setPalette(pal);

    MySocket::getInstance();
    connect(MySocket::getInstance(),SIGNAL(signal_login(QJsonValue&)),this,SLOT(slot_login(QJsonValue&)));

    //提示框
    messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("提示");
    messageBox->setWindowIcon(QIcon(":/images/img/2.ico"));
    messageBox->hide();

    widgetMain = new WidgetMain;
    widgetMain->hide();
}

//WidgetLogin::~WidgetLogin()
//{
//    delete ui;
//}

void WidgetLogin::on_regBtn_clicked()
{
    WidgetReg *widgetReg = new WidgetReg(this);
    widgetReg->show();
}

void WidgetLogin::on_findPwdBtn_clicked()
{
    WidgetFindPwd *widgetFindPwd = new WidgetFindPwd(this);
    widgetFindPwd->show();
}

void WidgetLogin::on_loginBtn_clicked()
{
    //装包
    QJsonObject json;
    json.insert("actionType","login");
    QJsonObject data;
    data.insert("userAccount",QJsonValue(ui->accountEdit->text()));
    data.insert("userPwd",QJsonValue(ui->pwdEdit->text()));
    json.insert("data",QJsonValue(data));

    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf<<endl;

}

void WidgetLogin::slot_login(QJsonValue &value_data)
{
    QJsonObject obj = value_data.toObject();
    QString result = obj.value("result").toString();
    if(result == "success"){
        User::getInstance()->setUserId(obj.value("userId").toInt());
        User::getInstance()->setUserName(obj.value("userName").toString());
        User::getInstance()->setHeadPortrait(obj.value("headportrait").toString());
        User::getInstance()->setMotto(obj.value("motto").toString());
        User::getInstance()->setArea(obj.value("area").toString());

        widgetMain->show();
        widgetMain->refreshBtn_clicked();
        this->hide();
    }else{
        messageBox->setText("账号或密码错误！");
        messageBox->exec();
    }
}
