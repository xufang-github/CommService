// utf8文件
#ifndef CDBCONNPOOL_GLOBAL_H
#define CDBCONNPOOL_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef CBADataService_LIB
#  define CBADataService_EXPORT Q_DECL_EXPORT
#else
#  define CBADataService_EXPORT Q_DECL_IMPORT
#endif

#endif // CDBCONNPOOL_GLOBAL_H
