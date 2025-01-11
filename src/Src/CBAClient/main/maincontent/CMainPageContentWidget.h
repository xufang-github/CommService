//utf-8 文件
#ifndef CMAINPAGECONTENTWIDGET_H
#define CMAINPAGECONTENTWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QHBoxLayout>

class CChatContentWidget;
class CPersonalInfoWidget;

class CMainPageContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMainPageContentWidget(QWidget *parent = nullptr);
    ~CMainPageContentWidget();

signals:
    void backClicked();  // 返回按钮点击信号
    void logoutClicked(); // 添加退出登录信号

public slots:
    void onChatGroupSelected(const QString& topic);
    void onPageChanged(int index);

private slots:
    void onBackButtonClicked();

private:
    void setupUI();
    void createChatPage();
    void createPersonalPage();
    void createTopBar();

private:
    QStackedWidget* m_stackedWidget;
    CChatContentWidget* m_chatContent;
    CPersonalInfoWidget* m_personalInfo;
    QPushButton* m_backButton;  // 返回按钮
    QWidget* m_topBar;  // 顶部栏
};

#endif // CMAINPAGECONTENTWIDGET_H
    