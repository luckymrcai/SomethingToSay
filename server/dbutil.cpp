#include "dbutil.h"

#include <QDebug>

DBUtil::DBUtil(QObject *parent) : QObject(parent)
{

}

QSqlDatabase DBUtil::getQSqlDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./SomethingToSay.db");

    bool ok = db.open();
    qDebug()<<"数据库链接："<<ok;

    QSqlQuery query;
    bool isq = query.exec("SELECT * FROM t_message order by createtime desc;");
    qDebug()<<"getQSqlDatabase()情况:"<<isq;
//    while (query.next()){

//        qDebug()<<query.value(0).toString()
//                <<query.value(1).toString()
//                <<query.value(2).toString()
//                <<query.value(3).toString()
//                <<query.value(4).toString()
//                <<query.value(5).toString();

//    }

    return db;
}
