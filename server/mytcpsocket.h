#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include "dbutil.h"
#include "public.h"

class MytcpSocket: public QTcpSocket
{
    Q_OBJECT

public:
    explicit MytcpSocket(qint32 socketDescriptor,QObject *parent = 0);
    void loginAction(QJsonDocument document);
    void regAction(QJsonDocument document);
    void findPwdAction(QJsonDocument document);
    void refreshAction(QJsonDocument document);
    void readMoreAction(QJsonDocument document);
    void postAction(QJsonDocument document);
    void collectAction(QJsonDocument document);
    void forwardAction(QJsonDocument document);
    void commentAction(QJsonDocument document);
    void likeAction(QJsonDocument document);
    void postCommentAction(QJsonDocument document);

    int maxMsgId = 0;
    int minMsgId = 0;

signals:
    void receiveData(qint32 socketDescriptor,const QByteArray &buf);

    void socketDisconnect(qint32 socketDescriptor);

public slots:
    void thisReadData();
};

#endif // MYTCPSOCKET_H
