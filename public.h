#ifndef PUBLIC_H
#define PUBLIC_H
#include <QString>

//登陆包
typedef struct login_t{
    QString userAccount;
    QString userPwd;
}LOGIN_T;


//注册
typedef struct reg_t{
    QString userAccount;
    QString userPwd;
    QString securityQuestion;
    QString securityAnswer;
}REG_T;

//忘记密码
typedef struct find_t{
    QString userAccount;
    QString userPwd;
    QString securityQuestion;
    QString securityAnswer;
}FIND_T;


//消息
typedef struct msg_t{
    int msgId = 0;
    int userId = 0;
    QString userName;
    QString headPortrait;
    QString createTime;
    QString area;
    QString content;
    bool isCollect = false;
    int forwardNum = 0;
    int commentNum = 0;
    int likeNum = 0;
    bool isLike = false;
}MSG_T;

//评论
typedef struct comment_t{
    int msgId = 0;
    int userId = 0;
    QString userName;
    QString headPortrait;
    QString createTime;
    QString content;
    int likeNum = 0;
}COMMENT_T;

#endif // PUBLIC_H
