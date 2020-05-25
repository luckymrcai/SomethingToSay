#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include <QTcpSocket>
#include <QByteArray>
#include "mytcpsocket.h"

class MyTcpServer :public QTcpServer
{
    Q_OBJECT

public:
    explicit MyTcpServer(QObject *parent = 0);

signals:
    void socketCountChange(const qint32 socketCount);

protected:
    void incomingConnection(qintptr handle);//用户连接，触发
public slots:
    void receiveDataSlot(const qint32 socketDescriptor,const QByteArray &buf);//信号由mytcpsocket发出
    void disconnectSlot(qint32 socketDescriptor);

private:
    QMap<qint32, MytcpSocket *> *clients;
};

#endif // MYTCPSERVER_H
