// sqlite用户服务类
#ifndef CBADataService_CSQLITEUSERSERVICE_H
#define CBADataService_CSQLITEUSERSERVICE_H
#include "CBADataService/CBADataService_global.h"
#include "IUserService.h"

namespace CBADataService
{
	class CSqliteUserService : public CBADataService::IUserService
	{
		public:
		CSqliteUserService();
		~CSqliteUserService();
		void createTableIfNoExit();
		//获取用户信息
		CBADataService::SUser getUserInfo(const QString& userName) override;
		//更新用户信息
		bool updateUserInfo(const CBADataService::SUser& user,const QString& userName) override;
		//删除用户信息
		void deleteUserInfo(const QString& userName) override;
		//添加用户信息
		bool addUserInfo(const CBADataService::SUser& user) override;
		// 登录验证
		bool login(const SUser& user) override;
		//查询所有用户信息
		QVector<SUser> getAllUsers() override;
	};
}


#endif // CBADataService_CSQLITEUSERSERVICE_H