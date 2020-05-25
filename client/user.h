#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
//    static WidgetLogin loginWidget;

    static User *getInstance(){
        if(user == nullptr){
            user = new User;
        }
        return user;
    }
    void setUserId(int userId);
    void setUserName(QString userName);
    void setHeadPortrait(QString headPortrait);
    void setMotto(QString motto);
    void setArea(QString area);
    int getUserId();
    QString getUserName();
    QString getHeadPortrait();
    QString getMotto();
    QString getArea();
private:
    User();
    static User *user;
    int userId;
    QString userName;
    QString headPortrait;
    QString motto;
    QString area;

};

#endif // USER_H
