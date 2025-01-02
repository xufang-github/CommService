// utf8文件
#ifndef CBACore_GLOBAL_H
#define CBACore_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef CBACore_LIB
#  define CBACore_EXPORT Q_DECL_EXPORT
#else
#  define CBACore_EXPORT Q_DECL_IMPORT
#endif

#endif // CBACore_GLOBAL_H
