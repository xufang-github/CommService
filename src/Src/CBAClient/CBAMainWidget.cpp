// utf8文件
#include "CBAMainWidget.h"
#include  "ui_CBAMainWidget.h"
#include <QTextStream>
#include "CBAClient/comm/CCommClient.h"
#include "main/CMainPageWidget.h"
#include "login/CBALoginWidget.h"
#include "settings/CSettingsWidget.h"

CBAMainWidget::CBAMainWidget(QWidget *parent)
	: QMainWindow(parent)
{
	this->connect(CCommClient::instance(),&CCommClient::sigLogin,
		this, &CBAMainWidget::slotLogin);
	ui = new Ui::CBAMainWidget();
	ui->setupUi(this);

	// 连接退出登录信号
	connect(ui->mainWidget, SIGNAL(logoutClicked()),
			this, SLOT(slotLogout()));
			
	// 连接设置按钮信号
	connect(ui->loginWidget, SIGNAL(showSettings()),
			this, SLOT(slotShowSettings()));
			
	// 连接设置页面返回信号
	connect(ui->settingsWidget, SIGNAL(backClicked()),
			this, SLOT(slotHideSettings()));
}

void CBAMainWidget::slotLogin(bool success) 
{
	if (success) 
	{
		ui->stackedWidget->setCurrentIndex(1);
	}
}

void CBAMainWidget::slotLogout()
{
	// 切换到登录页面
	ui->stackedWidget->setCurrentIndex(0);
	// 清空登录信息
	ui->loginWidget->clearLoginInfo();
}

void CBAMainWidget::slotShowSettings()
{
	ui->stackedWidget->setCurrentWidget(ui->settingsWidget);
}

void CBAMainWidget::slotHideSettings()
{
	ui->stackedWidget->setCurrentWidget(ui->loginWidget);
}

CBAMainWidget::~CBAMainWidget()
{
	delete ui;
}