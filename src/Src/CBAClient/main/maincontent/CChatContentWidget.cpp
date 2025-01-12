//utf-8 文件
#include "CChatContentWidget.h"
#include "CBAClient/comm/CCommClient.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDir>

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
    //m_chatDisplay->setOpenExternalLinks(true);
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
    loadHistoryMessages();
}

QString CChatContentWidget::getHistoryFilePath() const
{
    // 获取应用数据目录
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataPath + "/history");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    
    // 返回当前主题的历史记录文件路径
    return dir.filePath(m_currentTopic + ".json");
}

void CChatContentWidget::saveMessageToFile(const QString& timeStr, const QString& message)
{
    QFile file(getHistoryFilePath());
    QJsonArray messages;
    
    // 读取现有消息
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        if (doc.isArray()) {
            messages = doc.array();
        }
        file.close();
    }
    
    // 添加新消息
    QJsonObject newMessage;
    newMessage["time"] = timeStr;
    newMessage["content"] = message;
    messages.append(newMessage);
    
    // 限制消息数量
    while (messages.size() > MAX_HISTORY_MESSAGES) {
        messages.removeAt(0);
    }
    
    // 保存到文件
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(messages);
        file.write(doc.toJson());
        file.close();
    }
}

void CChatContentWidget::loadHistoryMessages()
{
    QFile file(getHistoryFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return;
    }
    
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    
    if (!doc.isArray()) {
        return;
    }
    
    QJsonArray messages = doc.array();
    for (const QJsonValue& value : messages) {
        QJsonObject msgObj = value.toObject();
        QString timeStr = msgObj["time"].toString();
        QString content = msgObj["content"].toString();
        
        if (m_currentTopic == "binance_news") {
            // 对于币安新闻，重新解析并显示
            appendMessage(content);
        } else {
            m_chatDisplay->append(QString("[%1] %2").arg(timeStr).arg(content));
        }
    }
    
    // 添加分隔线
    m_chatDisplay->append("----------------------------------------");
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
    
    // 检查是否是币安新闻主题
    if (m_currentTopic == "binance_news") {
        // 解析JSON消息
        QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
        if (doc.isObject()) {
            QJsonObject newsObj = doc.object();
            QString title = newsObj["title"].toString();
            QString url = newsObj["url"].toString();
            QString newsTime = newsObj["time"].toString();
            
            // 格式化显示新闻
            QString formattedNews = QString("<p>[%1]<br>"
                                          "<b>%2</b><br>"
                                          "<a href='%3'>查看详情</a><br>"
                                          "发布时间: %4</p>")
                                      .arg(timeStr)
                                      .arg(title)
                                      .arg(url)
                                      .arg(newsTime);
            
            m_chatDisplay->insertHtml(formattedNews);
        } else {
            m_chatDisplay->append(QString("[%1] %2").arg(timeStr).arg(message));
        }
    } else {
        // 普通消息直接显示
        m_chatDisplay->append(QString("[%1] %2").arg(timeStr).arg(message));
    }
    
    // 保存消息到文件
    saveMessageToFile(timeStr, message);
} 