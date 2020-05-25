#include "mytcpsocket.h"
#include <QSqlError>

MytcpSocket::MytcpSocket(qint32 socketDescriptor,QObject *parent): QTcpSocket(parent)
{
    this->setSocketDescriptor(socketDescriptor);
//    connect(this,&MytcpSocket::readyRead,[=](){
//        QByteArray b=this->readAll();
//        emit receiveData(socketDescriptor,b);
//    });
    connect(this,&MytcpSocket::readyRead,this,&MytcpSocket::thisReadData);

    connect(this,&MytcpSocket::disconnected,[=](){
        emit socketDisconnect(socketDescriptor);
    });
}


//判断事件
void MytcpSocket::thisReadData()
{
    QByteArray buf=this->readAll();
    qDebug()<<"客户端（"<<this->socketDescriptor()<<"）："<<buf;
    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(buf,&jsonError); // 转化为 JSON 文档
    if(!document.isNull() && jsonError.error == QJsonParseError::NoError){ // 解析未发生错误
        if(document.isObject()){ // JSON 文档为对象
            QJsonObject object = document.object(); // 转化为对象
            if(object.contains("actionType")){ // 包含指定的 key
                QJsonValue value = object.value("actionType"); // 获取指定 key 对应的 value
                if(value.isString()){ // 判断 value 是否为字符串
                    QString s_actionType = value.toString();
                    if(s_actionType == "login"){//登陆
                        loginAction(document);
                    }else if(s_actionType == "reg"){//注册
                        regAction(document);
                    }else if(s_actionType == "findPwd"){//找回密码
                        findPwdAction(document);
                    }else if(s_actionType == "refresh"){//第一次获取说说
                        refreshAction(document);
                    }else if(s_actionType == "readMore"){//获取旧的说说
                        readMoreAction(document);
                    }else if(s_actionType == "post"){//发布说说
                        postAction(document);
                    }else if(s_actionType == "collect"){//收藏
                        collectAction(document);
                    }else if(s_actionType == "forward"){//转发
                        forwardAction(document);
                    }else if(s_actionType == "comment"){//评论
                        commentAction(document);
                    }else if(s_actionType == "like"){//点赞
                        likeAction(document);
                    }else if(s_actionType == "postComment"){//发布评论
                        postCommentAction(document);
                    }





                }
            }
        }
    }
}
//登陆
void MytcpSocket::loginAction(QJsonDocument document)
{
    //解包
    QJsonObject obj = document.object();
    QJsonObject obj_data = obj.value("data").toObject();
    LOGIN_T login;
    login.userAccount = obj_data.value("userAccount").toString();
    login.userPwd = obj_data.value("userPwd").toString();

    QJsonObject object;
    //sql语句运行，运行失败退出
    QSqlQuery query;
    if(!query.exec("select userId from t_user where userAccount='"+login.userAccount+"' and userPwd='"+login.userPwd+"';")){
        qDebug()<<query.lastError();
        return ;
    }

    //有结果则登陆成功，没有则失败
    int userId=0;
    while(query.next()){
        userId = query.value(0).toInt();
    }
    if(userId != 0){
        if(!query.exec("select * from t_userInfo where userId = "+QString::number(userId))){
            qDebug()<<query.lastError();
            return ;
        }
        while(query.next()){
            object.insert("userId",query.value(0).toInt());
            object.insert("userName",query.value(1).toString());
            object.insert("headPortrait",query.value(2).toString());
            object.insert("motto",query.value(3).toString());
            object.insert("area",query.value(4).toString());
        }
        object.insert("result","success");
    }else{
        object.insert("result","error");
    }


    //装包
    obj.insert("data",QJsonValue(object));
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//注册
void MytcpSocket::regAction(QJsonDocument document)
{
    //解包
    QJsonObject obj = document.object();
    QJsonObject obj_data = obj.value("data").toObject();
    REG_T reg;
    reg.userAccount = obj_data.value("userAccount").toString();
    reg.userPwd = obj_data.value("userPwd").toString();
    reg.securityQuestion = obj_data.value("securityQuestion").toString();
    reg.securityAnswer = obj_data.value("securityAnswer").toString();

    //sql语句运行，运行失败退出
    QSqlQuery query;
    if(!query.exec("select * from t_user where userAccount='"+reg.userAccount+"'")){
        qDebug()<<query.lastError();
        return ;
    }

    //有结果则已存在该用户，没有则添加用户
    if(!query.next()){
        int count = 0;
        if(!query.exec("select count(*)from t_user;")){
            qDebug() << query.lastError();
            return ;
        }
        while (query.next()){
            count = query.value(0).toInt();
        }
        //添加用户
        query.prepare("insert into t_user values(?,?,?,?,?)");
        query.addBindValue(count+1);
        query.addBindValue(reg.userAccount);
        query.addBindValue(reg.userPwd);
        query.addBindValue(reg.securityQuestion);
        query.addBindValue(reg.securityAnswer);
        if(!query.exec()){
            qDebug() << query.lastError();
            return ;
        }
        //添加用户的默认用户名，地区等信息
        query.prepare("insert into t_userInfo values(?,?,?,?,?)");
        query.addBindValue(count+1);
        query.addBindValue("游客第"+QString::number(count+1)+"号");
        query.addBindValue(1);
        query.addBindValue("暂时无个人说明");
        query.addBindValue("未知地区");
        if(!query.exec()){
            qDebug() << query.lastError();
            return ;
        }
        //发布消息：我刚刚注册了有话说，成为了有话说第xxx用户，快来和我互动吧！
        if(!query.exec("select count(*) from t_message")){
            qDebug()<<query.lastError();
            return ;
        }
        int msgId = 0;
        while(query.next()){
            msgId = query.value(0).toInt();
        }
        QDateTime current_date_time = QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
        query.prepare("insert into t_message values (?,?,?,?,?)");
        query.addBindValue(msgId+1);
        query.addBindValue(count+1);
        query.addBindValue("我刚刚注册了有话说，成为了有话说第"+QString::number(count+1)+"位用户，快来和我互动吧！");
        query.addBindValue(current_date);
        query.addBindValue("未知地区");
        if(!query.exec()){
            qDebug() << query.lastError();
            return ;
        }

        obj.insert("data","success");
    }else{
        obj.insert("data","error");
    }

    //发包
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//找回密码
void MytcpSocket::findPwdAction(QJsonDocument document)
{
    //解包
    QJsonObject obj = document.object();
    QJsonObject obj_data = obj.value("data").toObject();
    FIND_T find;
    find.userAccount = obj_data.value("userAccount").toString();
    find.securityQuestion = obj_data.value("securityQuestion").toString();
    find.securityAnswer = obj_data.value("securityAnswer").toString();
    find.userPwd = obj_data.value("userPwd").toString();

    //数据库验证用户信息
    QSqlQuery query;
    query.prepare("select * from t_user where userAccount = :userAccount and "
                  "securityQuestion = :securityQuestion and "
                  "securityAnswer = :securityAnswer;");
    query.bindValue(":userAccount",find.userAccount);
    query.bindValue(":securityQuestion",find.securityQuestion);
    query.bindValue(":securityAnswer",find.securityAnswer);
    if(!query.exec()){
        qDebug() << query.lastError();
        return ;
    }

    //有结果数据则修改密码，无则失败
    if(query.next()){
        query.clear();
        query.prepare("update t_user set userPwd=:userPwd where userAccount=:userAccount");
        query.bindValue(":userPwd",find.userPwd);
        query.bindValue(":userAccount",find.userAccount);
        if(!query.exec()){
            qDebug() << query.lastError();
            return ;
        }
        obj.insert("data","success");
    }else{
        obj.insert("data","error");
    }

    //发包
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//刷新
void MytcpSocket::refreshAction(QJsonDocument document)
{
    QJsonObject obj= document.object();
    QJsonObject obj_data;
    QJsonArray array;
    MSG_T msg[10];

    //数据库查询：msgId,t_message.userId,userName,headPortrait,content,createTime,t_message.area
    QSqlQuery query,query2;
    query.prepare("select msgId,t_message.userId,userName,headPortrait,content,createTime,t_message.area "
                  "from t_message,t_userInfo where t_message.userId=t_userInfo.userId order by msgId desc limit 5;");
    if(!query.exec()){
        qDebug() << query.lastError();
        return ;
    }
    for(int i=0;query.next();i++){
        msg[i].msgId = query.value(0).toInt();
        msg[i].userId = query.value(1).toInt();
        msg[i].userName = query.value(2).toString();
        msg[i].headPortrait = query.value(3).toInt();
        msg[i].content = query.value(4).toString();
        msg[i].createTime = query.value(5).toString();
        msg[i].area = query.value(6).toString();

        //是否收藏
        query2.prepare("select * from t_collect where msgId=? and userId=?");
        query2.addBindValue(msg[i].msgId);
        query2.addBindValue(obj.value("data").toInt());
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg[i].isCollect = true;
        }
        //转发数量
        query2.prepare("select count(*) from t_forward where msgId=?");
        query2.addBindValue(msg[i].msgId);
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg[i].forwardNum = query2.value(0).toInt();
        }
        //评论数量
        query2.prepare("select count(*) from t_comment where msgId=?");
        query2.addBindValue(msg[i].msgId);
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg[i].commentNum = query2.value(0).toInt();
        }
        //点赞数量
        query2.prepare("select count(*) from t_like where msgId=?");
        query2.addBindValue(msg[i].msgId);
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg[i].likeNum = query2.value(0).toInt();
        }
        //是否点赞
        query2.prepare("select * from t_like where msgId=? and userId=?");
        query2.addBindValue(msg[i].msgId);
        query2.addBindValue(obj.value("data").toInt());
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg[i].isLike = true;
        }

        obj_data.insert("msgId",msg[i].msgId);
        obj_data.insert("userId",msg[i].userId);
        obj_data.insert("userName",msg[i].userName);
        obj_data.insert("headPortrait",msg[i].headPortrait);
        obj_data.insert("content",msg[i].content);
        obj_data.insert("createTime",msg[i].createTime);
        obj_data.insert("area",msg[i].area);
        obj_data.insert("isCollect",msg[i].isCollect);
        obj_data.insert("forwardNum",msg[i].forwardNum);
        obj_data.insert("commentNum",msg[i].commentNum);
        obj_data.insert("likeNum",msg[i].likeNum);
        obj_data.insert("isLike",msg[i].isLike);
        array.append(QJsonValue(obj_data));
        minMsgId = msg[i].msgId;

    }
    obj.insert("data",array);
    document.setObject(obj);

    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;

}
//查看更多
void MytcpSocket::readMoreAction(QJsonDocument document)
{
    QJsonObject obj= document.object();
    QJsonObject obj_data;
    QSqlQuery query,query2;

    MSG_T msg;
    msg.msgId = 0;
    query.prepare("select msgId,t_message.userId,userName,headPortrait,content,createTime,t_message.area "
                  "from t_message,t_userInfo where t_message.userId=t_userInfo.userId and t_message.msgId=?");

    query.addBindValue(minMsgId-1);
    if(!query.exec()){
        qDebug() << query.lastError();
        return ;
    }

    while (query.next()){
        msg.msgId = query.value(0).toInt();
        msg.userId = query.value(1).toInt();
        msg.userName = query.value(2).toString();
        msg.headPortrait = query.value(3).toString();
        msg.content = query.value(4).toString();
        msg.createTime = query.value(5).toString();
        msg.area = query.value(6).toString();
    }
    if(msg.msgId == 0){
        qDebug()<<"未查询到信息";
        obj.insert("data","All loaded");

    }else{
        this->minMsgId--;

        //是否收藏
        query2.prepare("select * from t_collect where msgId=? and userId=?");
        query2.addBindValue(msg.msgId);
        query2.addBindValue(obj.value("data").toInt());
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg.isCollect = true;
        }
        //转发数量
        query2.prepare("select count(*) from t_forward where msgId=?");
        query2.addBindValue(msg.msgId);
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg.forwardNum = query2.value(0).toInt();
        }
        //评论数量
        query2.prepare("select count(*) from t_comment where msgId=?");
        query2.addBindValue(msg.msgId);
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg.commentNum = query2.value(0).toInt();
        }
        //点赞数量
        query2.prepare("select count(*) from t_like where msgId=?");
        query2.addBindValue(msg.msgId);
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg.likeNum = query2.value(0).toInt();
        }
        //是否点赞
        query2.prepare("select * from t_like where msgId=? and userId=?");
        query2.addBindValue(msg.msgId);
        query2.addBindValue(obj.value("data").toInt());
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            msg.isLike = true;
        }
        obj_data.insert("msgId",msg.msgId);
        obj_data.insert("userId",msg.userId);
        obj_data.insert("userName",msg.userName);
        obj_data.insert("headPortrait",msg.headPortrait);
        obj_data.insert("content",msg.content);
        obj_data.insert("createTime",msg.createTime);
        obj_data.insert("area",msg.area);
        obj_data.insert("isCollect",msg.isCollect);
        obj_data.insert("forwardNum",msg.forwardNum);
        obj_data.insert("commentNum",msg.commentNum);
        obj_data.insert("likeNum",msg.likeNum);
        obj_data.insert("isLike",msg.isLike);
        obj.insert("data",obj_data);
    }
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;

}
//发布消息
void MytcpSocket::postAction(QJsonDocument document)
{
    QSqlQuery query;
    if(!query.exec("select count(*) from t_message")){
        qDebug()<<query.lastError();
        return ;
    }
    int msgId = 0;
    while(query.next()){
        msgId = query.value(0).toInt();
    }
    QJsonObject obj= document.object();
    QJsonObject obj_data=obj.value("data").toObject();
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    query.prepare("insert into t_message values (?,?,?,?,?)");
    query.addBindValue(msgId+1);
    query.addBindValue(obj_data.value("userId").toInt());
    query.addBindValue(obj_data.value("content"));
    query.addBindValue(current_date);
    query.addBindValue(obj_data.value("area"));
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    obj_data.insert("result","success");
    obj.insert("data",obj_data);
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//收藏
void MytcpSocket::collectAction(QJsonDocument document)
{
    QJsonObject obj = document.object();
    QJsonObject obj_data = obj.value("data").toObject();
    int msgId = obj_data.value("msgId").toInt();
    int userId = obj_data.value("userId").toInt();
    bool isCollect = obj_data.value("isCollect").toBool();
    QSqlQuery query;
    if(isCollect){
        query.prepare("delete from t_collect where msgId=? and userId=?");
        query.addBindValue(msgId);
        query.addBindValue(userId);

    }else{
        query.prepare("insert into t_collect values(?,?)");
        query.addBindValue(msgId);
        query.addBindValue(userId);
    }
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    obj_data.insert("result","success");
    obj.insert("data",obj_data);
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//转发
void MytcpSocket::forwardAction(QJsonDocument document)
{
    QJsonObject obj= document.object();
    QJsonObject obj_data=obj.value("data").toObject();
    QSqlQuery query;
    //表t_message添加信息
    if(!query.exec("select count(*) from t_message")){
        qDebug()<<query.lastError();
        return ;
    }
    int msgId = 0;
    while(query.next()){
        msgId = query.value(0).toInt();
    }
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    query.prepare("insert into t_message values (?,?,?,?,?)");
    query.addBindValue(msgId+1);
    query.addBindValue(obj_data.value("userId").toInt());
    query.addBindValue(obj_data.value("content"));
    query.addBindValue(current_date);
    query.addBindValue(obj_data.value("area"));
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    //表t_forward添加信息
    query.prepare("insert into t_forward values(?,?)");
    query.addBindValue(msgId);
    query.addBindValue(obj_data.value("userId").toInt());
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    //查询转发数量
    int forwardNum = 0;
    query.prepare("select count(*) from t_forward where msgId=?");
    query.addBindValue(msgId);
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    while(query.next()){
        forwardNum = query.value(0).toInt();
    }
    //发包
    obj_data.insert("forwardNum",forwardNum);
    obj_data.insert("result","success");
    obj.insert("data",obj_data);
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//评论
void MytcpSocket::commentAction(QJsonDocument document)
{
    QJsonObject obj= document.object();
    QJsonObject obj_data = obj.value("data").toObject();
    QJsonArray array;
    COMMENT_T comment_t;
    //数据库查询
    QSqlQuery query,query2;
    query.prepare("select * from t_comment where msgId=? order by createTime desc");
    query.addBindValue(obj_data.value("msgId").toInt());
    if(!query.exec()){
        qDebug() << query.lastError();
        return ;
    }
    for(int i=0;query.next();i++){
        comment_t.msgId = query.value(0).toInt();
        comment_t.userId = query.value(1).toInt();
        comment_t.content = query.value(2).toString();
        comment_t.createTime = query.value(3).toString();
        comment_t.likeNum = query.value(4).toInt();
        //用户名、头像
        query2.prepare("select * from t_userInfo where userId=?");
        query2.addBindValue(comment_t.userId);
        if(!query2.exec()){
            qDebug() << query.lastError();
            return ;
        }
        while(query2.next()){
            comment_t.userName = query2.value(1).toString();
            comment_t.headPortrait = query2.value(2).toString();
        }
        obj_data.insert("msgId",comment_t.msgId);
        obj_data.insert("userId",comment_t.userId);
        obj_data.insert("userName",comment_t.userName);
        obj_data.insert("headPortrait",comment_t.headPortrait);
        obj_data.insert("content",comment_t.content);
        obj_data.insert("createTime",comment_t.createTime);
        obj_data.insert("likeNum",comment_t.likeNum);
        array.append(QJsonValue(obj_data));
    }
    obj.insert("data",array);
    document.setObject(obj);

    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//点赞
void MytcpSocket::likeAction(QJsonDocument document)
{
    QJsonObject obj = document.object();
    QJsonObject obj_data = obj.value("data").toObject();
    int msgId = obj_data.value("msgId").toInt();
    int userId = obj_data.value("userId").toInt();
    bool isCollect = obj_data.value("isLike").toBool();
    QSqlQuery query;
    if(isCollect){
        query.prepare("delete from t_like where msgId=? and userId=?");
        query.addBindValue(msgId);
        query.addBindValue(userId);

    }else{
        query.prepare("insert into t_like values(?,?)");
        query.addBindValue(msgId);
        query.addBindValue(userId);
    }
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    int likeNum = 0;
    query.prepare("select count(*) from t_like where msgId=?");
    query.addBindValue(msgId);
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    while(query.next()){
        likeNum = query.value(0).toInt();
    }
    obj_data.insert("likeNum",likeNum);
    obj_data.insert("result","success");
    obj.insert("data",obj_data);
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
//发布评论
void MytcpSocket::postCommentAction(QJsonDocument document)
{
    QSqlQuery query;
    QJsonObject obj= document.object();
    QJsonObject obj_data=obj.value("data").toObject();
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
    query.prepare("insert into t_comment values (?,?,?,?,?)");
    query.addBindValue(obj_data.value("msgId").toInt());
    query.addBindValue(obj_data.value("userId").toInt());
    query.addBindValue(obj_data.value("content").toString());
    query.addBindValue(current_date);
    query.addBindValue(obj_data.value("likeNum"),0);
    if(!query.exec()){
        qDebug()<<query.lastError();
        return ;
    }
    obj_data.insert("result","success");
    obj.insert("data",obj_data);
    document.setObject(obj);
    QByteArray sendBuf = document.toJson(QJsonDocument::Compact);
    this->write(sendBuf);
    qDebug()<<"服务端："<<sendBuf;
}
