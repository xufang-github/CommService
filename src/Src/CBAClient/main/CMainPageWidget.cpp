// utf8文件
#include "CMainPageWidget.h"
#include <QTextStream>
#include <QSettings>
#include <QMessageBox>
#include <QGridLayout>
#include <QResizeEvent>
#include "maintab/CMainPageTabWidget.h"
#include "maincontent/CMainPageContentWidget.h"

#define SettingFile "CBAClient.ini"

CMainPageWidget::CMainPageWidget(QWidget *parent)
	: QWidget(parent),
	m_eLayoutType(ELayoutType::E_LAYOUT_NONE)
{
	m_pMainLayout = new QHBoxLayout(this);
	this->setLayout(m_pMainLayout);
	m_pContentWidget = new CMainPageContentWidget();
	m_pTabWidget = new CMainPageTabWidget();
	m_pMainLayout->addWidget(m_pTabWidget);
	m_pMainLayout->addWidget(m_pContentWidget);
	m_pMainLayout->setStretch(0, 1);
	m_pMainLayout->setStretch(1, 2);
	m_nCurrentIndex = 0;
	
	setupConnections();
	adjustLayout();
}

CMainPageWidget::~CMainPageWidget()
{
}

void CMainPageWidget::resizeEvent(QResizeEvent* e)
{
	adjustLayout();
	QWidget::resizeEvent(e);
}
void CMainPageWidget::showEvent(QShowEvent* e)
{
	adjustLayout();
	QWidget::showEvent(e);
}

CMainPageWidget::ELayoutType CMainPageWidget::calLayoutType()
{
	int nWidth = this->width();
	int nHeight = this->height();
	float fRatio = (float)nWidth / nHeight;
	if (fRatio > 1.5)
	{
		return ELayoutType::E_LAYOUT_PAD;
	}
	else
	{
		return ELayoutType::E_LAYOUT_PHONE;
	}
}

void CMainPageWidget::setupConnections()
{
	// 连接聊天组选择信号
	m_pTabWidget->connectToChatContent(m_pContentWidget);
	
	// 连接页面切换信号
	connect(m_pTabWidget, &CMainPageTabWidget::pageChanged,
			this, &CMainPageWidget::onPageChanged);
			
	// 连接退出登录信号
	connect(m_pContentWidget, &CMainPageContentWidget::logoutClicked,
			this, &CMainPageWidget::logoutClicked);
}

void CMainPageWidget::onPageChanged(int index)
{
	m_nCurrentIndex = index;
	
	// 在手机布局下切换显示
	if (m_eLayoutType == ELayoutType::E_LAYOUT_PHONE)
	{
		if (index == 0)
		{
			m_pTabWidget->show();
			m_pContentWidget->hide();
		}
		else
		{
			m_pTabWidget->hide();
			m_pContentWidget->show();
		}
	}
	
	// 更新内容页面
	m_pContentWidget->onPageChanged(index);
}

void CMainPageWidget::adjustLayout()
{
	// 如果布局未初始化，调整为手机布局
	if (m_eLayoutType == ELayoutType::E_LAYOUT_NONE)
	{
		m_eLayoutType = ELayoutType::E_LAYOUT_PHONE;
		onPageChanged(m_nCurrentIndex);
	}

	ELayoutType eLayoutType = calLayoutType();	
	if (m_eLayoutType != eLayoutType)
	{
		m_eLayoutType = eLayoutType;
		if (m_eLayoutType == ELayoutType::E_LAYOUT_PHONE)
		{
			onPageChanged(m_nCurrentIndex);
		}
		else if (m_eLayoutType == ELayoutType::E_LAYOUT_PAD)
		{
			m_pTabWidget->show();
			m_pContentWidget->show();
		}
	}
}