#include <QApplication>
#include <login/widget_login.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    WidgetLogin w;
//    w.show();

    WidgetLogin::getInstance()->show();
    return a.exec();
}
