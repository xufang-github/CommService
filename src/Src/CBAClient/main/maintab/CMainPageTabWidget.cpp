//utf-8 文件
#include "CMainPageTabWidget.h"
#include "ui_CMainPageTabWidget.h"
#include "CBAClient/main/maintab/CChatButton.h"
#include "CBAClient/main/maintab/CChatGroupWidget.h"
#include "CBAClient/main/maincontent/CMainPageContentWidget.h"

CMainPageTabWidget::CMainPageTabWidget(QWidget *parent) :    
    QWidget(parent),
    ui(new Ui::CMainPageTabWidget()),
    m_currentButton(nullptr),
    m_chatGroup(nullptr)
{
    ui->setupUi(this);
    
    // 添加聊天组页面
    m_chatGroup = new CChatGroupWidget(this);
    ui->stackedWidget->addWidget(m_chatGroup);
    
    // 添加个人信息页面
    QWidget* personPage = new QWidget(this);
    ui->stackedWidget->addWidget(personPage);
    
    // 创建底部按钮
    createTabButtons();
}

void CMainPageTabWidget::createTabButtons()
{
    // 聊天按钮
    CChatButton* chatBtn = new CChatButton(tr("聊天"), ui->widget);
    chatBtn->setCheckedStyle(":/global/chat_checked.png", QColor(255,0,0));
    chatBtn->setUnCheckedStyle(":/global/chat.png", QColor(0,0,0));
    chatBtn->setProperty("tabIndex", 0);
    chatBtn->setChecked(true);
    m_currentButton = chatBtn;
    ui->hLayout->addWidget(chatBtn);
    
    connect(chatBtn, &CChatButton::clicked, this, &CMainPageTabWidget::onTabButtonClicked);

    // 个人信息按钮
    CChatButton* personBtn = new CChatButton(tr("我的"), ui->widget);
    personBtn->setCheckedStyle(":/global/person_checked.png", QColor(255,0,0));
    personBtn->setUnCheckedStyle(":/global/person.png", QColor(0,0,0));
    personBtn->setProperty("tabIndex", 1);        
    ui->hLayout->addWidget(personBtn);
    
    connect(personBtn, &CChatButton::clicked, this, &CMainPageTabWidget::onTabButtonClicked);
}

void CMainPageTabWidget::onTabButtonClicked()
{
    CChatButton* btn = qobject_cast<CChatButton*>(sender());
    if (!btn || btn == m_currentButton)
        return;
        
    // 切换按钮状态
    if (m_currentButton)
        m_currentButton->setChecked(false);
        
    m_currentButton = btn;
    m_currentButton->setChecked(true);
    
    // 切换页面
    int index = btn->property("tabIndex").toInt();
    ui->stackedWidget->setCurrentIndex(index);
    
    // 通知内容页面切换
    emit pageChanged(index);
}

void CMainPageTabWidget::connectToChatContent(CMainPageContentWidget* content)
{
    if (m_chatGroup && content) {
        connect(m_chatGroup, &CChatGroupWidget::chatGroupSelected,
                content, &CMainPageContentWidget::onChatGroupSelected);
    }
}

CMainPageTabWidget::~CMainPageTabWidget()
{
    delete ui;
}
