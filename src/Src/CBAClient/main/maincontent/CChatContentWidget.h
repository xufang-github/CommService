//utf-8 文件
#ifndef CCHATCONTENTWIDGET_H
#define CCHATCONTENTWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>

class CChatContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CChatContentWidget(QWidget *parent = nullptr);
    void setTopic(const QString& topic);

private slots:
    void onSendMessage();
    void onMessageReceived(const QString& topic, const QString& message);

private:
    void setupUI();
    void appendMessage(const QString& message);

private:
    QTextEdit* m_chatDisplay;
    QLineEdit* m_messageInput;
    QString m_currentTopic;
};

#endif // CCHATCONTENTWIDGET_H 