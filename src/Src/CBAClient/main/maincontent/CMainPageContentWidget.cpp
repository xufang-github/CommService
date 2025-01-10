//utf-8 文件
#include "CMainPageContentWidget.h"
#include  <QHBoxLayout>

CMainPageContentWidget::CMainPageContentWidget(QWidget *parent) :
    QWidget(parent)
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);
	m_stackedWidget = new QStackedWidget(this);
	layout->addWidget(m_stackedWidget);

}

CMainPageContentWidget::~CMainPageContentWidget()
{

}