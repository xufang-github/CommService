// utf8文件
#include "CBALoginWidget.h"
#include  "ui_CBALoginWidget.h"
#include <QTextStream>
#include <QSettings>
#include "comm/CCommClient.h"
#include <QMessageBox>

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
	this->connect(CCommClient::instance(), &CCommClient::sigLogin,
		this, &CBALoginWidget::slotLogin);
	CCommClient::instance()->connectToServer(ip, port);
	// 绑定登录按钮
	this->connect(ui->loginBtn, &QPushButton::clicked, 
		[this]() 
	{
		SUser user;
		user.userName = ui->userName->text();
		user.password = ui->password->text();
		CCommClient::instance()->login(user);
	});
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