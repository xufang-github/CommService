#include <QFile>
#include <QDebug>

// utf8文件
#include "CBAMainWidget.h"
#include <QApplication>
#include <CBACore/CDBConnPool.h>

using namespace CBACore;

void InitSqlDatabase()
{
    // 检查数据库文件是否存在，如果不存在则创建
    QString dbFilePath = "database.db";
    if (!QFile::exists(dbFilePath)) {
        QFile dbFile(dbFilePath);
        if (!dbFile.open(QIODevice::WriteOnly)) {
            qCritical() << "无法创建数据库文件:" << dbFilePath;
            return;
        }
        dbFile.close();
    }
    // 初始化数据库连接池为本地的sqlite
    CDBConnPool::getInstance()->init(dbFilePath, "CBADATA", "", "", "QSQLITE", 10);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitSqlDatabase(); // 调用初始化数据库连接池函数
    CBAMainWidget w;
    w.show();
    return a.exec();
}