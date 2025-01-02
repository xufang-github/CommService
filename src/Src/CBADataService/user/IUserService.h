#ifndef CBADataService_IUserService_H_
#define CBADataService_IUserService_H_

#include <QString>
#include <QVector>
#include <CBADataService/CBADataService_global.h>

namespace CBADataService
{
	struct SUser 
	{
		QString userName = "";
		QString password = "";
	};

	class CBADataService_EXPORT IUserService
	{
	public:
		IUserService() {}
		virtual ~IUserService() {}
		// 获取实例
		static IUserService* getIntance();
		//获取用户信息
		virtual SUser getUserInfo(const QString& userName) { return {};}
		//更新用户信息
		virtual bool updateUserInfo(const SUser& user, const QString& userName) { return false; }
		//删除用户信息
		virtual void deleteUserInfo(const QString& userName) {}
		//添加用户信息
		virtual bool addUserInfo(const SUser& user) { return false; }
		// 登录验证
		virtual bool login(const SUser& user) { return false; }
		//查询所有用户信息
		virtual QVector<SUser> getAllUsers() { return {}; }
	};
}

#endif//CBADataService_IUserService_H_