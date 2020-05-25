#include "mytcpserver.h"
#include <QDebug>
#include <QThread>
#include <QByteArray>



MyTcpServer::MyTcpServer(QObject *parent): QTcpServer(parent)
{
    clients = new QMap< qint32, MytcpSocket *> ();
}

void MyTcpServer::incomingConnection(qint32 socketDescriptor)
{
    qDebug()<<"有新的链接 -socketDescriptor-"<<socketDescriptor;
    MytcpSocket *tcptemp = new MytcpSocket(socketDescriptor);
    QThread *thread = new QThread(tcptemp);
    //收到客户端发送的信息
    connect(tcptemp,&MytcpSocket::receiveData,this,&MyTcpServer::receiveDataSlot);
    //客户端断开链接
    connect(tcptemp,&MytcpSocket::socketDisconnect,this,&MyTcpServer::disconnectSlot);
    //客户端断开链接 关闭线程
    connect(tcptemp,&MytcpSocket::disconnected,thread,&QThread::quit);

    clients->insert(socketDescriptor,tcptemp);

    tcptemp->moveToThread(thread);
    thread->start();

    emit socketCountChange(clients->size());
    qDebug()<<"当前连接个数："<<clients->size();

}

void MyTcpServer::receiveDataSlot(const qint32 socketDescriptor,const QByteArray &buf)
{
    //根据数据actionType 类型判断客服端行为
    //{\"actionType\":\"login\",\"data\":{\"name\":\"小明\",\"pwd\":\"123456\"}}

//    QMap<int,QTcpSocket *>::iterator it=clients->find(socketDescriptor);
//    (*it)->write(buf);




}

void MyTcpServer::disconnectSlot(qint32 socketDescriptor)
{
    int i = clients->remove(socketDescriptor);
    qDebug()<<"删除客户端   i="<<i;
    emit socketCountChange(clients->size());
}
