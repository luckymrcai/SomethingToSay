#include "dbutil.h"
#include <QDebug>

DBUtil::DBUtil(QObject *parent) : QObject(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./SomethingToSay.db");

    bool ok = db.open();
    qDebug()<<"数据库链接："<<ok;

    QSqlQuery query;
    bool isq = query.exec("SELECT * FROM t_message;");
    qDebug()<<"数据库链接："<<isq;
    while (query.next()) {

    qDebug()<<query.value(0).toString()
            <<query.value(1).toString();

    }
}

