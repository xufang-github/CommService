// utf8文件
#include "IUserService.h"
#include "CSqliteUserService.h"

#include <CBACore/CDBConnPool.h>

using namespace CBADataService;
using namespace CBACore;

IUserService* IUserService::getIntance() 
{
	const QString& type = CDBConnPool::getInstance()->GetDirverType();
	if (type == "QSQLITE") 
	{
		return new CSqliteUserService();
	}
	else 
	{
		return new IUserService();
	}
}