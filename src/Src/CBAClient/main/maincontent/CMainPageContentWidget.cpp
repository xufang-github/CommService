//utf-8 文件
#include "CMainPageContentWidget.h"
#include "CChatContentWidget.h"
#include "CPersonalInfoWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

CMainPageContentWidget::CMainPageContentWidget(QWidget *parent) :
    QWidget(parent),
    m_stackedWidget(new QStackedWidget(this)),
    m_chatContent(nullptr),
    m_personalInfo(nullptr),
    m_backButton(nullptr),
    m_topBar(nullptr)
{
    setupUI();
}

CMainPageContentWidget::~CMainPageContentWidget()
{
}

void CMainPageContentWidget::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    
    createTopBar();
    createChatPage();
    createPersonalPage();
    
    layout->addWidget(m_topBar);
    layout->addWidget(m_stackedWidget);
    
    // 设置切换动画
    m_stackedWidget->setProperty("animated", true);
}

void CMainPageContentWidget::createChatPage()
{
    m_chatContent = new CChatContentWidget(this);
    m_stackedWidget->addWidget(m_chatContent);
}

void CMainPageContentWidget::createPersonalPage()
{
    m_personalInfo = new CPersonalInfoWidget(this);
    m_stackedWidget->addWidget(m_personalInfo);
}

void CMainPageContentWidget::createTopBar()
{
    m_topBar = new QWidget(this);
    QHBoxLayout* topLayout = new QHBoxLayout(m_topBar);
    m_topBar->setFixedHeight(40);
    
    m_backButton = new QPushButton(tr("退出登录"), this);
    connect(m_backButton, &QPushButton::clicked, this, &CMainPageContentWidget::onBackButtonClicked);
    
    topLayout->addWidget(m_backButton);
    topLayout->addStretch();
    
    // 默认隐藏顶部栏
    m_topBar->hide();
}

void CMainPageContentWidget::onBackButtonClicked()
{
    emit logoutClicked();
}

void CMainPageContentWidget::onChatGroupSelected(const QString& topic)
{
    if (m_chatContent) {
        m_chatContent->setTopic(topic);
        m_stackedWidget->setCurrentWidget(m_chatContent);
    }
}

void CMainPageContentWidget::onPageChanged(int index)
{
    m_stackedWidget->setCurrentIndex(index);
    
    // 在手机布局下显示返回按钮
    m_topBar->setVisible(index == 1);
    
    // 如果切换到个人信息页面，更新信息
    if (index == 1 && m_personalInfo) {
        m_personalInfo->updateUserInfo();
    }
}