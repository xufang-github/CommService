// utf8文件
#include "CommServiceWidget.h"
#include "ui_CommServiceWidget.h"
#include <QMessageBox.h>
#include "CBADataService/tcpservice/CCommService.h"
#include <QHostAddress>

using namespace CBADataService;

CommServiceWidget::CommServiceWidget(QWidget *parent)
    : QWidget(parent),
	ui(new Ui::CommServiceWidget)
{
	ui->setupUi(this);
	m_commService = new CCommService();
	quint16 port = 8080;
	do 
	{
		if (m_commService->listen(QHostAddress::Any, port)) 
		{
			break;
		}
		++port;
	} while (true);
	ui->port->setText(QString::number(port));
	ui->stateLabel->setChecked(true);

}

CommServiceWidget::~CommServiceWidget()
{
}