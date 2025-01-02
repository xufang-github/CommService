// utf8文件
#include "NewUserDialog.h"
#include "ui_NewUserDialog.h"

using namespace CBADataService;

NewUserDialog::NewUserDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::NewUserDialog())
{
    ui->setupUi(this);

    connect(ui->okButton, &QPushButton::clicked, this, &NewUserDialog::onAccept);
    connect(ui->cancelButton, &QPushButton::clicked, this, &NewUserDialog::reject);
}

QString NewUserDialog::getUserName() const
{
    return ui->userNameEdit->text();
}

QString NewUserDialog::getPassword() const
{
    return ui->passwordEdit->text();
}

void NewUserDialog::onAccept()
{
    if (!ui->userNameEdit->text().isEmpty() && !ui->passwordEdit->text().isEmpty()) {
        accept();
    }
}

void NewUserDialog::setUserName(const QString& userName) 
{
    ui->userNameEdit->setText(userName);
}
void NewUserDialog::setPassword(const QString& password) 
{
    ui->passwordEdit->setText(password);
}
