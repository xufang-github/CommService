//utf8文件 // utf8文件
#ifndef NEWUSERDIALOG_H
#define NEWUSERDIALOG_H

#include <QDialog>

namespace Ui 
{
    class NewUserDialog;
}
namespace CBADataService 
{
    class NewUserDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit NewUserDialog(QWidget *parent = nullptr);
        QString getUserName() const;
        QString getPassword() const;

        void setUserName(const QString &userName);
        void setPassword(const QString& password);

    private slots:
        void onAccept();

    private:
        Ui::NewUserDialog* ui;
    };
}

#endif // NEWUSERDIALOG_H
