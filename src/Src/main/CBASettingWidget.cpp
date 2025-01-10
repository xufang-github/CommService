// utf8文件
#include "CBASettingWidget.h"
#include  "ui_CBASettingWidget.h"
#include <QTextStream>
#include <QSettings>
#include "CBAClient/comm/CCommClient.h"
#include <QMessageBox>

#define SettingFile "CBAClient.ini"

CBASettingWidget::CBASettingWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::CBASettingWidget();
	ui->setupUi(this);
}

CBASettingWidget::~CBASettingWidget()
{
	delete ui;
}

void CBASettingWidget::slotLogin(bool success)
{

}