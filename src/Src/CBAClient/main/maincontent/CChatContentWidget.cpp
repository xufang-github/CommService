//utf-8 文件
#include "CChatContentWidget.h"
#include "CBAClient/comm/CCommClient.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTime>

CChatContentWidget::CChatContentWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    
    connect(CCommClient::instance(), &CCommClient::sigMessageReceived,
            this, &CChatContentWidget::onMessageReceived);
}

void CChatContentWidget::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    // 聊天显示区域
    m_chatDisplay = new QTextEdit(this);
    m_chatDisplay->setReadOnly(true);
    layout->addWidget(m_chatDisplay);
    
    // 底部发送区域
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    
    m_messageInput = new QLineEdit(this);
    connect(m_messageInput, &QLineEdit::returnPressed, this, &CChatContentWidget::onSendMessage);
    bottomLayout->addWidget(m_messageInput);
    
    QPushButton* sendBtn = new QPushButton(tr("发送"), this);
    connect(sendBtn, &QPushButton::clicked, this, &CChatContentWidget::onSendMessage);
    bottomLayout->addWidget(sendBtn);
    
    layout->addLayout(bottomLayout);
}

void CChatContentWidget::setTopic(const QString& topic)
{
    m_currentTopic = topic;
    m_chatDisplay->clear();
}

void CChatContentWidget::onSendMessage()
{
    QString message = m_messageInput->text().trimmed();
    if (message.isEmpty() || m_currentTopic.isEmpty())
        return;
        
    CCommClient::instance()->sendMessage(m_currentTopic, message);
    m_messageInput->clear();
}

void CChatContentWidget::onMessageReceived(const QString& topic, const QString& message)
{
    if (topic == m_currentTopic) {
        appendMessage(message);
    }
}

void CChatContentWidget::appendMessage(const QString& message)
{
    QString timeStr = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_chatDisplay->append(QString("[%1] %2").arg(timeStr).arg(message));
} 