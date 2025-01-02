// utf8文件
#include "CBAMainWidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBAMainWidget w;
    w.show();
    return a.exec();
}