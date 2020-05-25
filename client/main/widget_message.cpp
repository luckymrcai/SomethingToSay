#include "widget_message.h"
#include "ui_widget_message.h"

WidgetMessage::WidgetMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMessage)
{
    ui->setupUi(this);
    //消息背景
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(Qt::white));
    this->setPalette(pal);
    //this->setStyleSheet("QWidget{background-color:gray;border-top-left-radius:15px;border-top-right-radius:5px;}");

    this->resize(this->message_width,this->message_height);//界面大小
    ui->userContentLbl->setWordWrap(true);//设置自动换行
    ui->userContentLbl->move(20,80);
    ui->horizontalLayoutWidget->setFixedSize(this->width(),40);//点赞框大小

    //界面直线，2条横线，3条竖线
    pal.setBrush(QPalette::Background,QBrush(Qt::gray));
    hLineWidget1 = new QWidget(this);
    hLineWidget1->resize(this->width(),1);
    hLineWidget1->setAutoFillBackground(true);
    hLineWidget1->setPalette(pal);

    hLineWidget2 = new QWidget(this);
    hLineWidget2->resize(this->width(),1);
    hLineWidget2->setAutoFillBackground(true);
    hLineWidget2->setPalette(pal);

    vLineWidget1 = new QWidget(this);
    vLineWidget1->resize(1,ui->collectBtn->height() - 20);
    vLineWidget1->setAutoFillBackground(true);
    vLineWidget1->setPalette(pal);

    vLineWidget2 = new QWidget(this);
    vLineWidget2->resize(1,ui->collectBtn->height() - 20);
    vLineWidget2->setAutoFillBackground(true);
    vLineWidget2->setPalette(pal);

    vLineWidget3 = new QWidget(this);
    vLineWidget3->resize(1,ui->collectBtn->height() - 20);
    vLineWidget3->setAutoFillBackground(true);
    vLineWidget3->setPalette(pal);

    connect(MySocket::getInstance(),SIGNAL(signal_collect(QJsonValue&)),this,SLOT(slot_collect(QJsonValue&)));
    connect(MySocket::getInstance(),SIGNAL(signal_forward(QJsonValue&)),this,SLOT(slot_forward(QJsonValue&)));
    connect(MySocket::getInstance(),SIGNAL(signal_comment(QJsonValue&)),this,SLOT(slot_comment(QJsonValue&)));
    connect(MySocket::getInstance(),SIGNAL(signal_like(QJsonValue&)),this,SLOT(slot_like(QJsonValue&)));
}

WidgetMessage::~WidgetMessage()
{
    delete ui;
}

void WidgetMessage::setMyStytle()
{
    //互动栏
    if(msg.isCollect){
        ui->collectBtn->setIcon(QIcon(":/images/img/ICON/collect_hover.jpg"));
        ui->collectBtn->setText("已收藏");
    }
    if(msg.forwardNum){
        ui->forwardBtn->setText(QString::number(msg.forwardNum));
    }
    if(msg.commentNum){
        ui->commentBtn->setText(QString::number(msg.commentNum));
    }
    if(msg.likeNum){
        ui->likeBtn->setText(QString::number(msg.likeNum));
    }
    if(msg.isLike){
        ui->likeBtn->setIcon(QIcon(":/images/img/ICON/like_press.jpg"));
    }
    ui->userNameLbl->setText(msg.userName);
    ui->userAreaLbl->setText(msg.area);
    ui->userTimeLbl->setText(msg.createTime);
    ui->userContentLbl->setText(msg.content);
    ui->userContentLbl->adjustSize();//自适应大小
    ui->userContentLbl->setFixedWidth(this->width() - ui->userContentLbl->x()*2);

    ui->horizontalLayoutWidget->move(0,ui->userContentLbl->y() + ui->userContentLbl->height() + 20);
    this->setFixedHeight(ui->horizontalLayoutWidget->y() + ui->horizontalLayoutWidget->height());

    this->hLineWidget1->move(0,ui->horizontalLayoutWidget->y());
    this->hLineWidget2->move(0,ui->horizontalLayoutWidget->y() + ui->horizontalLayoutWidget->height() - 1);
    this->vLineWidget1->move(ui->horizontalLayoutWidget->width()/4*1,ui->horizontalLayoutWidget->y() + 10);
    this->vLineWidget2->move(ui->horizontalLayoutWidget->width()/4*2,ui->horizontalLayoutWidget->y() + 10);
    this->vLineWidget3->move(ui->horizontalLayoutWidget->width()/4*3,ui->horizontalLayoutWidget->y() + 10);

}

//按钮_收藏
void WidgetMessage::on_collectBtn_clicked()
{
    if(this->msg.isCollect){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("收藏");
        msgBox->setIcon(QMessageBox::Question);
        msgBox->setText("确定要取消吗?");
        QPushButton *okBtn = msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
        QPushButton *cancelBtn = msgBox->addButton(tr("取消"),QMessageBox::RejectRole);
        msgBox->exec();
        if (msgBox->clickedButton() == okBtn) {
            qDebug()<<"okBtn";
        } else if (msgBox->clickedButton() == cancelBtn) {
            return ;
        }
    }
    //装包
    QJsonObject json;
    json.insert("actionType","collect");
    QJsonObject data;
    data.insert("msgId",this->msg.msgId);
    data.insert("userId",User::getInstance()->getUserId());
    data.insert("isCollect",this->msg.isCollect);
    json.insert("data",data);
    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf;
}
//按钮_转发
void WidgetMessage::on_forwardBtn_clicked()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("转发说说");
    msgBox->setIcon(QMessageBox::Question);
    msgBox->setText("确定要转发吗?");
    QPushButton *okBtn = msgBox->addButton(tr("确定"),QMessageBox::AcceptRole);
    QPushButton *cancelBtn = msgBox->addButton(tr("取消"),QMessageBox::RejectRole);
    msgBox->exec();
    if (msgBox->clickedButton() == okBtn) {
        qDebug()<<"okBtn";
    } else if (msgBox->clickedButton() == cancelBtn) {
        return ;
    }
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    //装包
    QJsonObject json;
    json.insert("actionType","forward");
    QJsonObject data;
    data.insert("userId",User::getInstance()->getUserId());
    data.insert("content","转发：@"+msg.userName+"\n\n"+msg.content);
    data.insert("createTime",current_date);
    data.insert("area",User::getInstance()->getArea());
    data.insert("msgId",msg.msgId);
    json.insert("data",data);
    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf;
}
//按钮_评论
void WidgetMessage::on_commentBtn_clicked()
{
    WidgetComment *widgetComment = new WidgetComment(this);
    widgetComment->msg = this->msg;
    widgetComment->show();
}
//按钮_点赞
void WidgetMessage::on_likeBtn_clicked()
{
    //装包
    QJsonObject json;
    json.insert("actionType","like");
    QJsonObject data;
    data.insert("msgId",this->msg.msgId);
    data.insert("userId",User::getInstance()->getUserId());
    data.insert("isLike",this->msg.isLike);
    json.insert("data",data);
    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf;
}
//应答包_收藏
void WidgetMessage::slot_collect(QJsonValue &value_data)
{
    QJsonObject obj_data = value_data.toObject();
    if(obj_data.value("result") == "success" && obj_data.value("msgId") == msg.msgId){
        msg.isCollect = !msg.isCollect;
        if(msg.isCollect){
            ui->collectBtn->setIcon(QIcon(":/images/img/ICON/collect_hover.jpg"));
            ui->collectBtn->setText("已收藏");
        }else{
            ui->collectBtn->setIcon(QIcon(":/images/img/ICON/collect_normal.jpg"));
            ui->collectBtn->setText("收藏");
        }
    }
}
//应答包_转发
void WidgetMessage::slot_forward(QJsonValue &value_data)
{
    QJsonObject obj_data = value_data.toObject();
    if(obj_data.value("result") == "success" && obj_data.value("msgId") == msg.msgId){
        msg.forwardNum = obj_data.value("forwardNum").toInt();
        if(msg.forwardNum){
            ui->forwardBtn->setText(QString::number(msg.forwardNum));

        }else{
            ui->forwardBtn->setText("转发");
        }
        emit signal_forward_ok();
    }
}
//应答包_评论
void WidgetMessage::slot_comment(QJsonValue &value_data)
{

}
//应答包_点赞
void WidgetMessage::slot_like(QJsonValue &value_data)
{
    QJsonObject obj_data = value_data.toObject();
    if(obj_data.value("result") == "success" && obj_data.value("msgId") == msg.msgId){
        msg.isLike = !msg.isLike;
        msg.likeNum = obj_data.value("likeNum").toInt();
        if(msg.likeNum){
            ui->likeBtn->setText(QString::number(msg.likeNum));
        }else{
            ui->likeBtn->setText("点赞");
        }
        if(msg.isLike){
            ui->likeBtn->setIcon(QIcon(":/images/img/ICON/like_press.jpg"));
        }else{
            ui->likeBtn->setIcon(QIcon(":/images/img/ICON/like_normal.jpg"));
        }

    }
}


