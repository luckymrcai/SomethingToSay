#include "widget_select.h"
#include "ui_widget_select.h"
WidgetSelect::WidgetSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetSelect)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/img/2.ico"));

}

WidgetSelect::~WidgetSelect()
{
    delete ui;
}

void WidgetSelect::on_HappyBtn_clicked()
{
    WidgetMain *widget_main=new WidgetMain();
    widget_main->show();
    this->hide();
}

void WidgetSelect::on_SadBtn_clicked()
{
    WidgetMain *widget_main=new WidgetMain();
    widget_main->show();
    this->hide();
}
