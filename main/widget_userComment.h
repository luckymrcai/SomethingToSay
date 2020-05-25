#ifndef WIDGET_USERCOMMENT_H
#define WIDGET_USERCOMMENT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "public.h"

class WidgetUserComment : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetUserComment(QWidget *parent = 0);
    QPushButton *headPortraitBtn;
    QPushButton *likeBtn;
    QLabel *contentLbl;
    QLabel *usernameLbl;
    QLabel *createTimeLbl;
    QWidget *hLineWidget1;
    void setMyStyle();

    COMMENT_T com_t;

private slots:
    void likeBtn_clicked();

};

#endif // WIDGET_USERCOMMENT_H
