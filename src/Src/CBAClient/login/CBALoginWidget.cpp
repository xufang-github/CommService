// utf8文件
#include "CBALoginWidget.h"
#include "ui_CBALoginWidget.h"
#include <QTextStream>
#include <QSettings>
#include "../comm/CCommClient.h"
#include <QMessageBox>
#include <QApplication>

#define SettingFile "CBAClient.ini"

CBALoginWidget::CBALoginWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui = new Ui::CBALoginWidget();
	ui->setupUi(this);

	QSettings settings(SettingFile,QSettings::Format::IniFormat);
	QString ip = settings.value("ip","123.249.105.160").toString();
	//QString ip = settings.value("ip", "127.0.0.1").toString();
	quint16 port = (quint16)settings.value("port",8080).toUInt();
	
	setupConnections();
	
	CCommClient::instance()->connectToServer(ip, port);
}

void CBALoginWidget::setupConnections()
{
	// 连接登录信号
	connect(CCommClient::instance(), &CCommClient::sigLogin,
			this, &CBALoginWidget::slotLogin);
			
	// 绑定登录按钮
	connect(ui->loginBtn, &QPushButton::clicked, 
		[this]() 
	{
		SUser user;
		user.userName = ui->userName->text();
		user.password = ui->password->text();
		CCommClient::instance()->login(user);
	});
	
	// 绑定退出按钮
	connect(ui->exitBtn, &QPushButton::clicked,
			this, &CBALoginWidget::onExitButtonClicked);
	
	// 修改设置按钮连接
	connect(ui->settingBtn, &QPushButton::clicked,
			this, [this]() { emit showSettings(); });
}

void CBALoginWidget::onExitButtonClicked()
{
	// 弹出确认对话框
	QMessageBox::StandardButton reply = QMessageBox::question(
		this,
		tr("退出确认"),
		tr("确定要退出系统吗？"),
		QMessageBox::Yes | QMessageBox::No
	);
	
	if (reply == QMessageBox::Yes) {
		QApplication::quit();
	}
}

CBALoginWidget::~CBALoginWidget()
{
	delete ui;
}

void CBALoginWidget::slotLogin(bool success) 
{
	if(!success)
		QMessageBox::warning(this, "登录失败", "用户名或密码错误");
}

void CBALoginWidget::clearLoginInfo()
{
	// 清空用户名和密码输入框
	ui->userName->clear();
	ui->password->clear();
	
	// 取消已阅读选择
	ui->radioButton->setChecked(false);
	
	// 重置焦点到用户名输入框
	ui->userName->setFocus();
}