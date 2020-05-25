#include "widget_userComment.h"

WidgetUserComment::WidgetUserComment(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(610,400);
    this->setAutoFillBackground(true);
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(Qt::white));
    this->setPalette(pal);
    //按钮_头像
    headPortraitBtn = new QPushButton(this);
    headPortraitBtn->setIcon(QIcon(":/images/img/tx2.jpg"));
    headPortraitBtn->setIconSize(QSize(40,40));
    headPortraitBtn->setGeometry(20,10,40,40);
    //标签_用户名
    usernameLbl = new QLabel(this);
    usernameLbl->setGeometry(headPortraitBtn->x() + headPortraitBtn->width() +10,headPortraitBtn->y(),160,25);
    usernameLbl->setAlignment(Qt::AlignTop);
    usernameLbl->setText("拒绝刘亦菲1号:");
    usernameLbl->setStyleSheet("QLabel{background:transparent;font-family:微软雅黑;font:14px;color:#eb7350}");
    //标签_内容
    contentLbl = new QLabel(this);
    contentLbl->move(usernameLbl->x(),usernameLbl->y() + usernameLbl->height() + 5);
    contentLbl->setMinimumWidth(520);
    contentLbl->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    contentLbl->setStyleSheet("QLabel{font-family:微软雅黑;font:12px;color:#333333}");
    contentLbl->setWordWrap(true);
    contentLbl->setText("test");
    contentLbl->adjustSize();
    //标签_时间
    createTimeLbl = new QLabel(this);
    createTimeLbl->setText("2020-04-06 19:51");
    createTimeLbl->setGeometry(contentLbl->x(),contentLbl->y() + contentLbl->height(),160,25);
    createTimeLbl->setStyleSheet("QLabel{background:transparent;font-family:微软雅黑;font:12px;color:#808080}");
    //按钮_点赞
    likeBtn = new QPushButton(this);
    likeBtn->setIcon(QIcon(":/images/img/ICON/like_normal.jpg"));
    likeBtn->setIconSize(QSize(20,20));
    likeBtn->setText("赞");
    likeBtn->setCursor(QCursor(Qt::PointingHandCursor));
    likeBtn->setGeometry(contentLbl->x() + contentLbl->width() - 40,createTimeLbl->y(),40,20);
    likeBtn->setStyleSheet("QPushButton{background:transparent;font-family:微软雅黑;font:14px;color:#333333}"
                           "QPushButton::hover{color:#eb7350}");
    connect(likeBtn,SIGNAL(clicked(bool)),this,SLOT(likeBtn_clicked()));
    //横线
    pal.setBrush(QPalette::Background,QBrush(Qt::gray));
    hLineWidget1 = new QWidget(this);
    hLineWidget1->setGeometry(20,createTimeLbl->y() + createTimeLbl->height() + 10,575,1);
    hLineWidget1->setAutoFillBackground(true);
    hLineWidget1->setPalette(pal);

    this->setFixedHeight(hLineWidget1->y() + 10);
}

void WidgetUserComment::setMyStyle()
{
    usernameLbl->setText(this->com_t.userName);
    contentLbl->setText(this->com_t.content);
    contentLbl->adjustSize();
    createTimeLbl->setText(this->com_t.createTime);
    createTimeLbl->move(contentLbl->x(),contentLbl->y() + contentLbl->height());
    likeBtn->move(contentLbl->x() + contentLbl->width() - 40,createTimeLbl->y());
    hLineWidget1->move(20,createTimeLbl->y() + createTimeLbl->height() + 10);
    this->setFixedHeight(hLineWidget1->y() + 10);
//    if(this->com_t.likeNum == 0){
//        likeBtn->setText("赞");
//        likeBtn->setIcon(QIcon(":/images/img/ICON/like_normal.jpg"));
//    }else{
//        likeBtn->setText(QString::number(this->com_t.likeNum));
//        likeBtn->setIcon(QIcon(":/images/img/ICON/like_press.jpg"));
//    }
    likeBtn->hide();
}
//按钮_给评论点赞
void WidgetUserComment::likeBtn_clicked()
{

}


