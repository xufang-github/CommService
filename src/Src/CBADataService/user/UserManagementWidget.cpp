// utf8文件// utf8文件
#include "UserManagementWidget.h"
#include "ui_UserManagementWidget.h"
#include "IUserService.h"
#include "NewUserDialog.h"
#include <QMessageBox.h>

using namespace CBADataService;

UserManagementWidget::UserManagementWidget(QWidget *parent)
    : QWidget(parent),
	ui(new Ui::UserManagementWidget)
{
	ui->setupUi(this);
    loadUsers();
	// 表格高度自适应
	ui->userTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

UserManagementWidget::~UserManagementWidget()
{
}

void UserManagementWidget::on_addUserBtn_clicked()
{
    NewUserDialog dialog;
	if (dialog.exec() == QDialog::Accepted) {
		SUser user;
		user.userName = dialog.getUserName();
		user.password = dialog.getPassword();
		if (IUserService::getIntance()->addUserInfo(user))
		{
			loadUsers();
		}
		else 
		{
			QMessageBox::warning(this, tr("Warning"), tr("Add user failed!"));
		}
	}
}


void UserManagementWidget::loadUsers() 
{
	// 清空表格，并释放内存
	ui->userTable->clearContents();
	ui->userTable->setRowCount(0);
	auto users = IUserService::getIntance()->getAllUsers();
	ui->userTable->setRowCount(users.size());
	for (int i = 0; i < users.size(); i++) 
	{
		auto user = users[i];
		ui->userTable->setItem(i, 0, new QTableWidgetItem(QString::number(i+1)));
		ui->userTable->setItem(i, 1, new QTableWidgetItem(user.userName));
		ui->userTable->setItem(i, 2, new QTableWidgetItem(user.password));
		// 设置表格内容居中
		ui->userTable->item(i, 0)->setTextAlignment(Qt::AlignCenter);
		ui->userTable->item(i, 1)->setTextAlignment(Qt::AlignCenter);
		ui->userTable->item(i, 2)->setTextAlignment(Qt::AlignCenter);
		// 在表格中添加删除、编辑按钮
		auto deleteBtn = new QPushButton(tr("删除"));
		auto editBtn = new QPushButton(tr("编辑"));
		connect(deleteBtn, &QPushButton::clicked, [this, user] {
			IUserService::getIntance()->deleteUserInfo(user.userName);
			loadUsers();
		});
		connect(editBtn, &QPushButton::clicked, [this, user] {
			NewUserDialog dialog;
			dialog.setUserName(user.userName);
			dialog.setPassword(user.password);
			if (dialog.exec() == QDialog::Accepted) {
				SUser newUser;
				newUser.userName = dialog.getUserName();
				newUser.password = dialog.getPassword();
				if (IUserService::getIntance()->updateUserInfo(newUser, user.userName))
				{
					loadUsers();
				}
				else
				{
					QMessageBox::warning(this, tr("Warning"), tr("Update user failed!"));
				}
			}
		});
		// 将两个按钮合并到一列
		auto layout = new QHBoxLayout();
		layout->addWidget(deleteBtn);
		layout->addWidget(editBtn);
		auto widget = new QWidget();
		widget->setLayout(layout);
		ui->userTable->setCellWidget(i, 3, widget);
	}
}
