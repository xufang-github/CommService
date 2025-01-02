//utf8文件
#ifndef _CBADataService_CommServiceWidget_H
#define _CBADataService_CommServiceWidget_H

#include "CBADataService/CBADataService_global.h"
#include <QWidget>

namespace Ui
{
    class CommServiceWidget;
}

namespace CBADataService
{
    class CCommService;
    class CBADataService_EXPORT CommServiceWidget : public QWidget
    {
        Q_OBJECT
    public:
        explicit CommServiceWidget(QWidget* parent = nullptr);
        ~CommServiceWidget();
    private:
        Ui::CommServiceWidget* ui;
        CBADataService::CCommService* m_commService;
    };
}

#endif // _CBADataService_CommServiceWidget_H
