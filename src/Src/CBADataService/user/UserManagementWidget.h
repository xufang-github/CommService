//utf8文件
#ifndef USERMANAGEMENTWIDGET_H
#define USERMANAGEMENTWIDGET_H

#include "CBADataService/CBADataService_global.h"
#include <QWidget>

namespace Ui
{
    class UserManagementWidget;
}

namespace CBADataService
{
    class CBADataService_EXPORT UserManagementWidget : public QWidget
    {
        Q_OBJECT
    public:
        explicit UserManagementWidget(QWidget* parent = nullptr);
        ~UserManagementWidget();
    private slots:
        void on_addUserBtn_clicked();
    private:
        void loadUsers();
    private:
        Ui::UserManagementWidget* ui;

    };
}

#endif // USERMANAGEMENTWIDGET_H
