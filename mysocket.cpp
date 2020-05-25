#include "mysocket.h"
#include <QDebug>

MySocket *MySocket::socket = 0;

MySocket::MySocket()
    :QTcpSocket()
{
    connectToHost(QHostAddress("127.0.0.1"),9999,QTcpSocket::ReadWrite);
    connect(this,&QTcpSocket::connected,this,&MySocket::connected);
    connect(this,&QTcpSocket::readyRead,this,&MySocket::receiveDataSlot);

}

void MySocket::connected()
{
    qDebug()<<"与服务器连接成功"<<endl;
}

void MySocket::receiveDataSlot()
{
    QByteArray buf = socket->readAll();
    qDebug()<<"服务端："<<buf;

    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(buf,&jsonError); // 转化为 JSON 文档
    if(!doc.isNull() && jsonError.error == QJsonParseError::NoError){ // 解析未发生错误
        QJsonObject object = doc.object(); // 转化为对象
        if(object.contains("actionType")){ // 包含指定的 key

            QJsonValue value = object.value("actionType"); // 获取指定 key 对应的 value

//            QJsonObject obj_data = object.value("data").toObject();

            QJsonValue value_data = object.value("data");
                        qDebug()<<value_data.toString();
                if(value.toString() == "login"){
                    emit signal_login(value_data);
                }else if(value.toString() == "reg"){
                    emit signal_reg(value_data);
                }else if(value.toString() == "findPwd"){
                    emit signal_findPwd(value_data);
                }else if(value.toString() == "refresh"){
                    emit signal_refresh(value_data);
                }else if(value.toString() == "readMore"){
                    emit signal_readMore(value_data);
                }else if(value.toString() == "post"){
                    emit signal_post(value_data);
                }else if(value.toString() == "collect"){
                    emit signal_collect(value_data);
                }else if(value.toString() == "forward"){
                    emit signal_forward(value_data);
                }else if(value.toString() == "comment"){
                    emit signal_comment(value_data);
                }else if(value.toString() == "like"){
                    emit signal_like(value_data);
                }else if(value.toString() == "postComment"){
                    emit signal_postComment(value_data);
                }
        }

    }
}
