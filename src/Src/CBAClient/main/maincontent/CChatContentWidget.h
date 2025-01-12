//utf-8 文件
#ifndef CCHATCONTENTWIDGET_H
#define CCHATCONTENTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QPushButton>

class CChatContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CChatContentWidget(QWidget *parent = nullptr);
    void setTopic(const QString& topic);

private slots:
    void onSendMessage();
    void onMessageReceived(const QString& topic, const QString& message);
    void onLoadMoreMessages();
    void onClearHistory();
    void onScrollValueChanged(int value);

private:
    void setupUI();
    void appendMessage(const QString& message);
    void saveMessageToFile(const QString& timeStr, const QString& message);
    void loadHistoryMessages(int offset = 0, int limit = 10);
    QString getHistoryFilePath() const;
    void updateLoadMoreButton();

private:
    QTextEdit* m_chatDisplay;
    QLineEdit* m_messageInput;
    QString m_currentTopic;
    QPushButton* m_loadMoreBtn;
    QPushButton* m_clearHistoryBtn;
    int m_currentOffset;
    static const int MAX_HISTORY_MESSAGES = 100; // 最大历史消息数
    static const int PAGE_SIZE = 10; // 每页加载消息数
};

#endif // CCHATCONTENTWIDGET_H