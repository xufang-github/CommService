//utf-8 文件
#include "CChatGroupWidget.h"
#include "ui_CChatGroupWidget.h"
#include "CBAClient/comm/CCommClient.h"
#include <QVBoxLayout>
#include <QPushButton>

CChatGroupWidget::CChatGroupWidget(QWidget *parent) :    
    QWidget(parent),
    ui(new Ui::CChatGroupWidget())
{
    ui->setupUi(this);
    
    // 连接通信客户端的消息信号
    connect(CCommClient::instance(), &CCommClient::sigMessageReceived,
            this, &CChatGroupWidget::onMessageReceived);
            
    // 初始化聊天组
    initChatGroups();
}

CChatGroupWidget::~CChatGroupWidget()
{
    delete ui;
}

void CChatGroupWidget::initChatGroups()
{
    // 添加默认聊天组
    addChatGroup("公共聊天室", "public");
    addChatGroup("币安新闻", "binance_news");
    addChatGroup("技术交流", "tech");
    addChatGroup("休闲娱乐", "entertainment");
}

void CChatGroupWidget::addChatGroup(const QString& name, const QString& topic)
{
    QPushButton* groupBtn = new QPushButton(name, this);
    groupBtn->setProperty("topic", topic);
    groupBtn->setCheckable(true);
    groupBtn->setAutoExclusive(true);
    
    connect(groupBtn, &QPushButton::clicked, this, &CChatGroupWidget::onGroupSelected);
    
    ui->layout->addWidget(groupBtn);
    m_chatGroups[topic] = groupBtn;
    
    // 订阅该主题
    CCommClient::instance()->subscribe(topic);
}

void CChatGroupWidget::onGroupSelected()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    
    QString topic = btn->property("topic").toString();
    emit chatGroupSelected(topic);
}

void CChatGroupWidget::onMessageReceived(const QString& topic, const QString& message)
{
    // 如果收到消息的主题存在对应的群组按钮
    if (m_chatGroups.contains(topic)) {
        QPushButton* btn = m_chatGroups[topic];
        // TODO: 可以在这里添加未读消息提醒等功能
    }
}
