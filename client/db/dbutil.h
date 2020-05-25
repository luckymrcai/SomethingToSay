#ifndef DBUTIL_H
#define DBUTIL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class DBUtil : public QObject
{
    Q_OBJECT
public:
    static DBUtil *getInstance(){
        if(dbuil == nullptr){
            dbuil = new DBUtil();
        }
        return dbuil;
    }

private:
    DBUtil(QObject *parent = 0);
    static DBUtil *dbuil;
};

#endif // DBUTIL_H
