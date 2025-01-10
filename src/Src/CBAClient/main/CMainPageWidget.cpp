// utf8文件
#include "CBAClient/main/CMainPageWidget.h"
#include <QTextStream>
#include <QSettings>
#include <QMessageBox>
#include  <QGridLayout>
#include "CBAClient/main/maintab/CMainPageTabWidget.h"
#include "CBAClient/main/maincontent/CMainPageContentWidget.h"

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

void CMainPageWidget::adjustLayout()
{
	// 如果布局未初始化，调整为手机布局
	if (m_eLayoutType == ELayoutType::E_LAYOUT_NONE)
	{
		m_eLayoutType = ELayoutType::E_LAYOUT_PHONE;
		if (m_nCurrentIndex == 0)
		{
			m_pTabWidget->show();
			m_pContentWidget->hide();
		}
		else
		{
			m_pContentWidget->show();
			m_pTabWidget->hide();
		}
	}

	ELayoutType eLayoutType = calLayoutType();	
	if (m_eLayoutType != eLayoutType)
	{
		m_eLayoutType = eLayoutType;
		if (m_eLayoutType == ELayoutType::E_LAYOUT_PHONE)
		{
			if (m_nCurrentIndex == 0)
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
		else  if (m_eLayoutType == ELayoutType::E_LAYOUT_PAD)
		{
			m_pTabWidget->show();
			m_pContentWidget->show();
		}
	}
}