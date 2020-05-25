#include "user.h"

User *User::user = 0;

User::User()
{

}

void User::setUserId(int userId)
{
    this->userId = userId;
}

void User::setUserName(QString userName)
{
    this->userName = userName;
}

void User::setHeadPortrait(QString headPortrait)
{
    this->headPortrait = headPortrait;
}

void User::setMotto(QString motto)
{
    this->motto = motto;
}

void User::setArea(QString area)
{
    this->area = area;
}

int User::getUserId()
{
    return userId;
}

QString User::getUserName()
{
    return userName;
}

QString User::getHeadPortrait()
{
    return headPortrait;
}

QString User::getMotto()
{
    return motto;
}

QString User::getArea()
{
    return area;
}


