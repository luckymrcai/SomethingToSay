#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
class MySocket :public QTcpSocket
{
    Q_OBJECT
public:
    static MySocket *getInstance(){
        if(socket == nullptr){
            socket = new MySocket;
        }
        return socket;
    }

private:
    MySocket();
    static MySocket *socket;
signals:

    void signal_login(QJsonValue &value_data);
    void signal_reg(QJsonValue &value_data);
    void signal_findPwd(QJsonValue &value_data);
    void signal_refresh(QJsonValue &value_data);
    void signal_readMore(QJsonValue &value_data);
    void signal_post(QJsonValue &value_data);
    void signal_collect(QJsonValue &value_data);
    void signal_forward(QJsonValue &value_data);
    void signal_comment(QJsonValue &value_data);
    void signal_like(QJsonValue &value_data);
    void signal_postComment(QJsonValue &value_data);
public slots:
    void connected();
    void receiveDataSlot();


};

#endif // MYSOCKET_H
