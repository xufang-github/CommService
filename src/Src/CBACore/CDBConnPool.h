//utf8文件 
// 基于qt的数据库连接池类
#ifndef CBACore_CDBConnPoo_H_
#define CBACore_CDBConnPoo_H_

#include <QtSql/QSqlDatabase>
#include <QtCore/QMutex>
#include <QtCore/QQueue>
#include <QtCore/QWaitCondition>

#include "CBACore_global.h"

namespace CBACore 
{
    class  CBACore_EXPORT CDBConnPool {
        public:
            static CDBConnPool* getInstance();
            CDBConnPool();
            ~CDBConnPool();
            //初始化数据库连接池
            void init(const QString& hostName, const QString& dbName, const QString& userName, const QString& password, const QString& driverType, int maxConnectionCount = 5);
            void initByJsonFile(const QString& joinFile);
            //获取数据库连接
            QSqlDatabase getDatabase();
            //释放数据库连接
            void releaseDatabase(QSqlDatabase db);
            //获取数据库连接池实例
            inline  const QString& GetDirverType() const { return m_driverType; }
    private:
            //创建数据库连接
            QSqlDatabase createConnection(const QString& connectionName);
            //释放所有连接
            void releaseAllConn();
        private:
            QString m_hostName;
            QString m_dbName;
            QString m_userName;
            QString m_password;
            QString m_driverType;
            int m_maxConnectionCount;
            QMutex m_mutex;
            QWaitCondition m_waitCondition;
            QQueue<QString> m_usedConnectionNames;
            QQueue<QString> m_unusedConnectionNames;
            static CDBConnPool* s_instance;
    };
}

#endif // !CBACore_CDBConnPoo_H_