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
#include <QScrollBar>
#include <QMessageBox>

CChatContentWidget::CChatContentWidget(QWidget *parent)
    : QWidget(parent)
    , m_currentOffset(0)
{
    setupUI();
    
    connect(CCommClient::instance(), &CCommClient::sigMessageReceived,
            this, &CChatContentWidget::onMessageReceived);
}

void CChatContentWidget::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    
    // 加载更多按钮
    m_loadMoreBtn = new QPushButton(tr("加载更多"), this);
    m_loadMoreBtn->hide();
    connect(m_loadMoreBtn, &QPushButton::clicked, this, &CChatContentWidget::onLoadMoreMessages);
    layout->addWidget(m_loadMoreBtn);
    
    // 聊天显示区域
    m_chatDisplay = new QTextEdit(this);
    m_chatDisplay->setReadOnly(true);
    connect(m_chatDisplay->verticalScrollBar(), &QScrollBar::valueChanged,
            this, &CChatContentWidget::onScrollValueChanged);
    layout->addWidget(m_chatDisplay);
    
    // 底部发送区域
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    
    m_messageInput = new QLineEdit(this);
    connect(m_messageInput, &QLineEdit::returnPressed, this, &CChatContentWidget::onSendMessage);
    bottomLayout->addWidget(m_messageInput);
    
    QPushButton* sendBtn = new QPushButton(tr("发送"), this);
    connect(sendBtn, &QPushButton::clicked, this, &CChatContentWidget::onSendMessage);
    bottomLayout->addWidget(sendBtn);
    
    // 清空历史按钮
    m_clearHistoryBtn = new QPushButton(tr("清空历史"), this);
    connect(m_clearHistoryBtn, &QPushButton::clicked, this, &CChatContentWidget::onClearHistory);
    bottomLayout->addWidget(m_clearHistoryBtn);
    
    layout->addLayout(bottomLayout);
}

void CChatContentWidget::setTopic(const QString& topic)
{
    m_currentTopic = topic;
    m_chatDisplay->clear();
    m_currentOffset = 0;
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

void CChatContentWidget::loadHistoryMessages(int offset, int limit)
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
    int totalMessages = messages.size();
    int startIndex = qMax(0, totalMessages - offset - limit);
    int endIndex = qMax(0, totalMessages - offset);
    
    // 如果是加载更多，插入到文本开头
    QString tempText;
    QTextCursor cursor(m_chatDisplay->document());
    cursor.movePosition(QTextCursor::Start);
    
    for (int i = startIndex; i < endIndex; ++i) {
        QJsonObject msgObj = messages[i].toObject();
        QString timeStr = msgObj["time"].toString();
        QString content = msgObj["content"].toString();
        
        QString messageText;
        if (m_currentTopic == "binance_news") {
            // 对于币安新闻，重新解析并显示
            QJsonDocument newsDoc = QJsonDocument::fromJson(content.toUtf8());
            if (newsDoc.isObject()) {
                QJsonObject newsObj = newsDoc.object();
                messageText = QString("[%1] %2\n链接: %3\n发布时间: %4\n")
                    .arg(timeStr)
                    .arg(newsObj["title"].toString())
                    .arg(newsObj["url"].toString())
                    .arg(newsObj["time"].toString());
            }
        } else {
            messageText = QString("[%1] %2\n").arg(timeStr).arg(content);
        }
        
        if (offset > 0) {
            tempText.prepend(messageText);
        } else {
            m_chatDisplay->append(messageText);
        }
    }
    
    if (offset > 0) {
        cursor.insertText(tempText);
        cursor.insertText("\n");
    }
    
    // 更新加载更多按钮状态
    m_loadMoreBtn->setVisible(startIndex > 0);
    m_currentOffset = offset + limit;
}

void CChatContentWidget::onLoadMoreMessages()
{
    loadHistoryMessages(m_currentOffset, PAGE_SIZE);
}

void CChatContentWidget::onClearHistory()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        tr("确认清空"),
        tr("确定要清空所有历史消息吗？"),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        QFile file(getHistoryFilePath());
        if (file.open(QIODevice::WriteOnly)) {
            file.write("[]");
            file.close();
            
            m_chatDisplay->clear();
            m_currentOffset = 0;
            m_loadMoreBtn->hide();
        }
    }
}

void CChatContentWidget::onScrollValueChanged(int value)
{
    // 当滚动到顶部时自动加载更多
    if (value == 0 && m_loadMoreBtn->isVisible()) {
        onLoadMoreMessages();
    }
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