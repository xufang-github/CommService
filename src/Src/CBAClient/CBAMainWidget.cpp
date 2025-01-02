// utf8文件
#include "CBAMainWidget.h"
#include  "ui_CBAMainWidget.h"
#include <QTextStream>
#include <comm/CCommClient.h>

CBAMainWidget::CBAMainWidget(QWidget *parent)
	: QMainWindow(parent)
{
	this->connect(CCommClient::instance(),&CCommClient::sigLogin,
		this, &CBAMainWidget::slotLogin);
	ui = new Ui::CBAMainWidget();
	ui->setupUi(this);

}

void CBAMainWidget::slotLogin(bool success) 
{
	if (success) 
	{
		ui->stackedWidget->setCurrentIndex(1);
	}
}

CBAMainWidget::~CBAMainWidget()
{
	delete ui;
}