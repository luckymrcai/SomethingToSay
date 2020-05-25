#include "widget_comment.h"

WidgetComment::WidgetComment(WidgetMessage *widgetMessage_1, QWidget *parent): QWidget(parent)
{
    this->setFixedSize(650,810);
    //滚动区
    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(0,0,650,810);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //滚动界面
    scrollWidget = new QWidget(scrollArea);
    scrollWidget->resize(629,410);//减去滚动条宽度
    scrollArea->setWidget(scrollWidget);
    //消息框
    widgetMessage = new WidgetMessage(scrollWidget);
    widgetMessage->msg = widgetMessage_1->msg;
    widgetMessage->setMyStytle();
    widgetMessage->move(10,10);

    //下部分界面
    widget_bottom = new QWidget(scrollWidget);
    widget_bottom->setGeometry(10,widgetMessage->height()-29,widgetMessage->width(),120);
    widget_bottom->setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(Qt::white));
    widget_bottom->setPalette(pal);
    y = widget_bottom->y() + widget_bottom->height();
    //按钮_头像
    headPortraitBtn = new QPushButton(widget_bottom);
    headPortraitBtn->setIcon(QIcon(":/images/img/tx2.jpg"));
    headPortraitBtn->setIconSize(QSize(40,40));
    headPortraitBtn->setGeometry(20,10,40,40);
    //编辑框_评论
    textEdit = new QTextEdit(widget_bottom);
    textEdit->setGeometry(70,10,520,50);
    //按钮_评论
    commentBtn = new QPushButton(widget_bottom);
    commentBtn->setGeometry(530,70,60,30);
    commentBtn->setText("评论");
    commentBtn->setCursor(QCursor(Qt::PointingHandCursor));
    commentBtn->setStyleSheet("QPushButton{background-color:#ff8140;color:white;font-family:微软雅黑;border-radius:4px;}"
                              "QPushButton::hover{background-color:#f7671d;}");
    connect(commentBtn,SIGNAL(clicked(bool)),this,SLOT(commentBtn_clicked()));
    //横线
//    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(Qt::gray));
    QWidget *hLineWidget1 = new QWidget(widget_bottom);
    hLineWidget1->setGeometry(20,commentBtn->y() + commentBtn->height() + 10,widget_bottom->width()-40,1);
    hLineWidget1->setAutoFillBackground(true);
    hLineWidget1->setPalette(pal);
    //请求包_评论
    request_comment_bag();

    scrollWidget->setFixedHeight(widgetMessage->height() + widget_bottom->height());
    connect(MySocket::getInstance(),SIGNAL(signal_comment(QJsonValue&)),this,SLOT(slot_comment(QJsonValue&)));
    connect(MySocket::getInstance(),SIGNAL(signal_postComment(QJsonValue&)),this,SLOT(slot_postComment(QJsonValue&)));
}
//请求包_评论
void WidgetComment::request_comment_bag()
{
    QJsonObject json;
    json.insert("actionType","comment");
    QJsonObject data;
    data.insert("msgId",widgetMessage->msg.msgId);
    data.insert("userId",User::getInstance()->getUserId());
    json.insert("data",data);
    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf;
    this->textEdit->clear();
}
//按钮_评论
void WidgetComment::commentBtn_clicked()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    //装包
    QJsonObject json;
    json.insert("actionType","postComment");
    QJsonObject data;
    data.insert("msgId",widgetMessage->msg.msgId);
    data.insert("userId",User::getInstance()->getUserId());
    data.insert("content",this->textEdit->toPlainText());
    data.insert("createTime",current_date);
    data.insert("likeNum",0);
    json.insert("data",data);
    //发包
    QJsonDocument doc;
    doc.setObject(json);
    QByteArray buf = doc.toJson(QJsonDocument::Compact);
    MySocket::getInstance()->write(buf);
    qDebug()<<"客户端："<<buf;
    this->textEdit->clear();

}
//应答包_评论
void WidgetComment::slot_comment(QJsonValue &value_data)
{
    //解包
    QJsonArray array_data = value_data.toArray();
    for(int i=0;i < array_data.size();i++){
        QJsonObject obj_data = array_data.at(i).toObject();
        WidgetUserComment *widgetUserComment = new WidgetUserComment(scrollWidget);
        widgetUserComment->com_t.msgId = obj_data.value("msgId").toInt();
        widgetUserComment->com_t.userId = obj_data.value("userId").toInt();
        widgetUserComment->com_t.headPortrait = obj_data.value("headPortrait").toString();
        widgetUserComment->com_t.userName = obj_data.value("userName").toString();
        widgetUserComment->com_t.content = obj_data.value("content").toString();
        widgetUserComment->com_t.createTime = obj_data.value("createTime").toString();
        widgetUserComment->com_t.likeNum = obj_data.value("likeNum").toInt();
        widgetUserComment->setMyStyle();
        widgetUserComment->move(10,y);
        widgetUserComment->show();
        y += widgetUserComment->height();
        scrollWidget->setFixedHeight(y);
        list_com.push_back(widgetUserComment);
    }
}

void WidgetComment::slot_postComment(QJsonValue &value_data)
{
    QJsonObject obj = value_data.toObject();
    if(obj.value("result") == "success"){
        QList<WidgetUserComment *>::Iterator it = list_com.begin();
        for(it=list_com.begin();it!=list_com.end();it++){
            delete (*it);
            list_com.pop_front();
        }
        y = widget_bottom->y() + widget_bottom->height();
        request_comment_bag();
    }
}
