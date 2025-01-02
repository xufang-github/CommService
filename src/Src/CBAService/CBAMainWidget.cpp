// utf8文件
#include "CBAMainWidget.h"
#include  "ui_CBAMainWidget.h"

CBAMainWidget::CBAMainWidget(QWidget* parent)
	: QMainWindow(parent)
{
	ui = new Ui::CBAMainWidget();
	ui->setupUi(this);
}

CBAMainWidget::~CBAMainWidget()
{
	delete ui;
}