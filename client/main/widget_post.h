#ifndef WIDGET_POST_H
#define WIDGET_POST_H

#include <QWidget>
#include <QMessageBox>
#include "mysocket.h"
#include "user.h"
namespace Ui {
class WidgetPost;
}

class WidgetPost : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPost(QWidget *parent = 0);
    ~WidgetPost();

private slots:
    void on_backBtn_clicked();

    void on_postBtn_clicked();

private:
    Ui::WidgetPost *ui;
};

#endif // WIDGET_POST_H
