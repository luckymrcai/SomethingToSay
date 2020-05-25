#include "widget_main.h"


WidgetMain::WidgetMain(QWidget *parent) :
    QWidget(parent)
{
    qDebug()<<"widget_main";
    //定义界面大小
    this->setFixedSize(WINDOWS_WIDTH,WINDOWS_HEIGHT);
    this->setWindowIcon(QIcon(":/images/img/2.ico"));
    //滚动区
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(0,0,WINDOWS_WIDTH,WINDOWS_HEIGHT);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    connect(scrollArea->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(slot_scroolWidget(int)));
    //滚动界面
    scrollWidget = new QWidget(scrollArea);
    scrollWidget->resize(WINDOWS_WIDTH-21,WINDOWS_HEIGHT);//减去滚动条宽度
    scrollArea->setWidget(scrollWidget);
    //上部分界面
    widgetTop = new WidgetMainTop(this);
    widgetTop->setGeometry(0,0,this->WINDOWS_WIDTH,50);
    connect(widgetTop->refreshBtn,SIGNAL(clicked()),this,SLOT(refreshBtn_clicked()));
    connect(widgetTop->postBtn,SIGNAL(clicked()),this,SLOT(postBtn_clicked()));
    //发布消息界面
    widgetPost = new WidgetPost();
    widgetPost->hide();
    //查看更多
    lookMoreBtn = new QPushButton("查看更多>",scrollWidget);
    lookMoreBtn->resize(610,35);
    lookMoreBtn->setCursor(QCursor(Qt::PointingHandCursor));
    lookMoreBtn->setStyleSheet("QPushButton{border-radius:3px; background-color: white; color: black; font-size: 15px;font-family:微软雅黑}"
                                   "QPushButton:hover{color:#EB7350; font-size: 15px;}"
                                   "QPushButton:pressed{color:#EB7350; font-size: 15px;}");
    lookMoreBtn->move((scrollWidget->width()-lookMoreBtn->width())/2,scrollWidget->height()-lookMoreBtn->height()-10);
    lookMoreBtn->show();
    connect(this->lookMoreBtn,SIGNAL(clicked()),this,SLOT(lookMoreBtn_clicked()));
    //提示框
    messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("提示");
    messageBox->setText("到底了！");
    messageBox->setWindowIcon(QIcon(":/images/img/2.ico"));
    //设置界面
    widgetSet = new WidgetSet(this);
    widgetSet->setGeometry(widgetTop->setBtn->x()-40,45,100,105);
    widgetSet->hide();
    connect(widgetTop->setBtn,SIGNAL(clicked(bool)),this,SLOT(setBtn_clicked()));
    //socket
    connect(MySocket::getInstance(),SIGNAL(signal_refresh(QJsonValue&)),this,SLOT(slot_refresh(QJsonValue&)));
    connect(MySocket::getInstance(),SIGNAL(signal_readMore(QJsonValue&)),this,SLOT(slot_readMore(QJsonValue&)));
    connect(MySocket::getInstance(),SIGNAL(signal_post(QJsonValue&)),this,SLOT(slot_post(QJsonValue&)));

}

WidgetMain::~WidgetMain()
{
    delete this;
}

//按钮_刷新
void WidgetMain::refreshBtn_clicked()
{
    this->widgetTop->nameBtn->setText(User::getInstance()->getUserName());

    QJsonObject json;
    json.insert("actionType","refresh");
    json.insert("data",User::getInstance()->getUserId());
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray b=doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(b);
}
//按钮_查看更多
void WidgetMain::lookMoreBtn_clicked()
{
    QJsonObject json;
    json.insert("actionType","readMore");
    json.insert("data",User::getInstance()->getUserId());
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray b=doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(b);
}
//按钮_发布消息
void WidgetMain::postBtn_clicked()
{
    widgetPost->show();
}
//按钮_设置
void WidgetMain::setBtn_clicked()
{
    static bool ok = true;
    if(ok){
        widgetSet->show();
    }else{
        widgetSet->hide();
    }
    ok = !ok;
}
//按钮_用户名
void WidgetMain::nameBtn_clicked()
{

}
//滚动条到底
void WidgetMain::slot_scroolWidget(int value)
{
    if(value == scrollArea->verticalScrollBar()->maximum()){
        lookMoreBtn->click();
    }

}
//应答包_刷新
void WidgetMain::slot_refresh(QJsonValue &data_value)
{
    //消息界面初始化
    scrollWidget->resize(WINDOWS_WIDTH-21,WINDOWS_HEIGHT);
    message_y=70;
    QList<WidgetMessage *>::Iterator it = list_msg.begin();
    for(it=list_msg.begin();it!=list_msg.end();it++){
        delete (*it);
        list_msg.pop_front();
    }
//    _sleep(100);
    //解包
    QJsonArray array_data = data_value.toArray();
    for(int i=0;i < array_data.size();i++){
        QJsonObject obj_data = array_data.at(i).toObject();
        WidgetMessage *m = new WidgetMessage(scrollWidget);
        m->msg.msgId = obj_data.value("msgId").toInt();
        m->msg.userId = obj_data.value("userId").toInt();
        m->msg.userName = obj_data.value("userName").toString();
        m->msg.headPortrait = obj_data.value("headPortrait").toString();
        m->msg.content = obj_data.value("content").toString();
        m->msg.createTime = obj_data.value("createTime").toString();
        m->msg.area = obj_data.value("area").toString();
        m->msg.isCollect = obj_data.value("isCollect").toBool();
        m->msg.forwardNum = obj_data.value("forwardNum").toInt();
        m->msg.commentNum = obj_data.value("commentNum").toInt();
        m->msg.likeNum = obj_data.value("likeNum").toInt();
        m->msg.isLike = obj_data.value("isLike").toBool();
        m->connect(m,SIGNAL(signal_forward_ok()),this,SLOT(slot_forward_ok()));
        m->setMyStytle();
        m->move(this->message_x,this->message_y);
        m->show();

        //调整消息界面的位置大小
        this->message_y += m->height() + message_space;
        lookMoreBtn->move(lookMoreBtn->x(),this->message_y+5);
        scrollWidget->resize(scrollWidget->width(),lookMoreBtn->y()+lookMoreBtn->height()+5);//重置页面大小
        list_msg.push_back(m);
    }

}
//应答包_查看更多
void WidgetMain::slot_readMore(QJsonValue &data_value)
{
    QJsonObject obj_data = data_value.toObject();
    if(data_value.toString() == "All loaded"){

        messageBox->show();
        return ;
    }

    WidgetMessage *m = new WidgetMessage(scrollWidget);
    m->msg.msgId = obj_data.value("msgId").toInt();
    m->msg.userId = obj_data.value("userId").toInt();
    m->msg.userName = obj_data.value("userName").toString();
    m->msg.headPortrait = obj_data.value("headPortrait").toString();
    m->msg.content = obj_data.value("content").toString();
    m->msg.createTime = obj_data.value("createTime").toString();
    m->msg.area = obj_data.value("area").toString();
    m->msg.isCollect = obj_data.value("isCollect").toBool();
    m->msg.forwardNum = obj_data.value("forwardNum").toInt();
    m->msg.commentNum = obj_data.value("commentNum").toInt();
    m->msg.likeNum = obj_data.value("likeNum").toInt();
    m->msg.isLike = obj_data.value("isLike").toBool();
    m->connect(m,SIGNAL(signal_forward_ok()),this,SLOT(slot_forward_ok()));
    m->setMyStytle();
    m->move(this->message_x,this->message_y);
    m->show();

    //调整消息界面的位置大小
    this->message_y += m->height() + message_space;
    lookMoreBtn->move(lookMoreBtn->x(),this->message_y+5);
    scrollWidget->resize(scrollWidget->width(),lookMoreBtn->y()+lookMoreBtn->height()+5);//重置页面大小
    list_msg.push_back(m);
}
//应答包_发布
void WidgetMain::slot_post(QJsonValue &value_data)
{
    QJsonObject obj = value_data.toObject();
    if(obj.value("result") == "success"){
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("提示");
        messageBox->setWindowIcon(QIcon(":/images/img/2.ico"));
        messageBox->setText("发布成功");
        messageBox->exec();
        widgetTop->refreshBtn->click();
    }
}
//应答包_转发成功
void WidgetMain::slot_forward_ok()
{
    QMessageBox *messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("提示");
    messageBox->setWindowIcon(QIcon(":/images/img/2.ico"));
    messageBox->setText("转发成功");
    messageBox->exec();
    widgetTop->refreshBtn->click();
}






