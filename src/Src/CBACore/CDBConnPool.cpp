// utf8文件
#include "CDBConnPool.h"
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace CBACore;

CDBConnPool* CDBConnPool::s_instance = new CDBConnPool;

CDBConnPool::CDBConnPool() 
    : m_hostName(""), 
    m_dbName(""), 
    m_userName(""), 
    m_password(""), 
    m_driverType(""),
    m_maxConnectionCount(0)
{
    
}

CDBConnPool::~CDBConnPool() 
{
    QMutexLocker locker(&m_mutex);
    while (!m_usedConnectionNames.isEmpty()) {
        QString connectionName = m_usedConnectionNames.dequeue();
        QSqlDatabase::removeDatabase(connectionName);
    }
    while (!m_unusedConnectionNames.isEmpty()) {
        QString connectionName = m_unusedConnectionNames.dequeue();
        QSqlDatabase::removeDatabase(connectionName);
    }
}

// 初始化数据库连接池
void CDBConnPool::init(const QString& hostName, const QString& dbName, const QString& userName, const QString& password, const QString& driverType, int maxConnectionCount)
{
    m_hostName = hostName;
    m_dbName = dbName;
    m_userName = userName;
    m_password = password;
    m_driverType = driverType;
    m_maxConnectionCount = maxConnectionCount;
}

void CDBConnPool::initByJsonFile(const QString& jsonFile)
{
    QFile file(jsonFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open JSON file:" << jsonFile;
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    if (document.isNull() || !document.isObject()) {
        qDebug() << "Invalid JSON document:" << jsonFile;
        return;
    }

    QJsonObject jsonObject = document.object();
    m_hostName = jsonObject.value("hostName").toString();
    m_dbName = jsonObject.value("dbName").toString();
    m_userName = jsonObject.value("userName").toString();
    m_password = jsonObject.value("password").toString();
    m_driverType = jsonObject.value("driverType").toString();
    m_maxConnectionCount = jsonObject.value("maxConnectionCount").toInt();
}

// 获取数据库连接
QSqlDatabase CDBConnPool::getDatabase()
{
    QMutexLocker locker(&m_mutex);

    while (m_unusedConnectionNames.isEmpty() && m_usedConnectionNames.size() >= m_maxConnectionCount) {
        m_waitCondition.wait(&m_mutex);
    }

    if (!m_unusedConnectionNames.isEmpty()) {
        QString connectionName = m_unusedConnectionNames.dequeue();
        m_usedConnectionNames.enqueue(connectionName);
        return QSqlDatabase::database(connectionName);
    }

    QString connectionName = QString("Connection-%1").arg(m_usedConnectionNames.size() + m_unusedConnectionNames.size());
    QSqlDatabase db = createConnection(connectionName);
    if (db.isOpen()) {
        m_usedConnectionNames.enqueue(connectionName);
        return db;
    }

    return QSqlDatabase();
}

// 释放数据库连接
void CDBConnPool::releaseDatabase(QSqlDatabase db)
{
    QMutexLocker locker(&m_mutex);
    QString connectionName = db.connectionName();
    if (m_usedConnectionNames.contains(connectionName)) {
        m_usedConnectionNames.removeOne(connectionName);
        m_unusedConnectionNames.enqueue(connectionName);
        m_waitCondition.wakeOne();
    }
}

// 创建数据库连接
QSqlDatabase CDBConnPool::createConnection(const  QString& connectionName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(m_driverType, connectionName);
    db.setHostName(m_hostName);
    db.setDatabaseName(m_dbName);
    db.setUserName(m_userName);
    db.setPassword(m_password);

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    }

    return db;
}

void CDBConnPool::releaseAllConn()
{
    	QMutexLocker locker(&m_mutex);
	while (!m_usedConnectionNames.isEmpty()) {
		QString connectionName = m_usedConnectionNames.dequeue();
		QSqlDatabase::removeDatabase(connectionName);
	}
	while (!m_unusedConnectionNames.isEmpty()) {
		QString connectionName = m_unusedConnectionNames.dequeue();
		QSqlDatabase::removeDatabase(connectionName);
	}
}

CDBConnPool* CDBConnPool::getInstance()
{
	return s_instance;
}
