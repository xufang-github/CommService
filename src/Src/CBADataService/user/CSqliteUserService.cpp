// utf8文件
#include "CSqliteUserService.h"

#include <CBACore/CDBConnPool.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>


using namespace CBADataService;
using namespace CBACore;


void CSqliteUserService::createTableIfNoExit() 
{
    QSqlDatabase db = CDBConnPool::getInstance()->getDatabase();
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS users (userName TEXT PRIMARY KEY, password TEXT)");
        CDBConnPool::getInstance()->releaseDatabase(db);
    } else {
        qDebug() << "Failed to get database connection";
    }
}

CSqliteUserService::CSqliteUserService():IUserService()
{
    createTableIfNoExit();
}

CSqliteUserService::~CSqliteUserService()
{
}

// 获取用户信息
SUser CSqliteUserService::getUserInfo(const QString& userName)
{
    SUser user;
    QSqlDatabase db = CDBConnPool::getInstance()->getDatabase();
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.prepare("SELECT userName, password FROM users WHERE userName = :userName");
        query.bindValue(":userName", userName);

        if (query.exec()) {
            if (query.next()) {
                user.userName = query.value(0).toString();
                user.password = query.value(1).toString();
            }
        } else {
            qDebug() << "Failed to get user info:" << query.lastError().text();
        }
        CDBConnPool::getInstance()->releaseDatabase(db);
    } else {
        qDebug() << "Failed to get database connection";
    }

    return user;
}

// 更新用户信息
bool CSqliteUserService::updateUserInfo(const SUser& user, const QString& userName)
{
    QSqlDatabase db = CDBConnPool::getInstance()->getDatabase();
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.prepare("UPDATE users SET password = :password,userName = :userName WHERE userName = :id");
        query.bindValue(":password", user.password);
        query.bindValue(":userName", user.userName);
        query.bindValue(":id", userName);

        if (!query.exec()) {
            qDebug() << "Failed to update user info:" << query.lastError().text();
            return false;
        }
        CDBConnPool::getInstance()->releaseDatabase(db);
        return true;
    }
    else {
        qDebug() << "Failed to get database connection";
        return false;
    }
   
}

// 删除用户信息
void CSqliteUserService::deleteUserInfo(const QString& userName)
{
    QSqlDatabase db = CDBConnPool::getInstance()->getDatabase();
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.prepare("DELETE FROM users WHERE userName = :userName");
        query.bindValue(":userName", userName);

        if (!query.exec()) {
            qDebug() << "Failed to delete user info:" << query.lastError().text();
        }
        CDBConnPool::getInstance()->releaseDatabase(db);
    } else {
        qDebug() << "Failed to get database connection";
    }
}

// 添加用户信息
bool CSqliteUserService::addUserInfo(const SUser& user)
{
    QSqlDatabase db = CDBConnPool::getInstance()->getDatabase();
    if (db.isOpen()) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO users (userName, password) VALUES (:userName, :password)");
        query.bindValue(":userName", user.userName);
        query.bindValue(":password", user.password);

        if (!query.exec()) {
            qDebug() << "Failed to add user info:" << query.lastError().text();
            return false;
        }
        CDBConnPool::getInstance()->releaseDatabase(db);
        return true;
    } else {
        qDebug() << "Failed to get database connection";
        return false;
    }
}

QVector<SUser> CSqliteUserService::getAllUsers() 
{
    QVector<SUser> users;
	QSqlDatabase db = CDBConnPool::getInstance()->getDatabase();
	if (db.isOpen()) {
		QSqlQuery query(db);
		query.exec("SELECT userName, password FROM users");

		while (query.next()) {
			SUser user;
			user.userName = query.value(0).toString();
			user.password = query.value(1).toString();
			users.push_back(user);
		}
		CDBConnPool::getInstance()->releaseDatabase(db);
	} else {
		qDebug() << "Failed to get database connection";
	}

	return users;
}


bool CSqliteUserService::login(const SUser& user) 
{
    SUser userInDB = getUserInfo(user.userName);
	if (userInDB.userName.isEmpty()) {
		return false;
	}
	return userInDB.password == user.password;
}

