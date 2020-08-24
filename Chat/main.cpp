#include "chat.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMap<QString,QString> map;
    map.insert("user","Mariae");
    map.insert("img",":/Icons/1.jpg");
    map.insert("id","1724236802@qq.com");
    Chat w(map);
    w.show();

    return a.exec();
}
