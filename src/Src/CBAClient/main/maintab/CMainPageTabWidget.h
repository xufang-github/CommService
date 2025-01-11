//utf-8 文件
#ifndef CMAINPAGETABWIDGET_1_H
#define CMAINPAGETABWIDGET_1_H

#include <QWidget>

class CChatButton;
class CChatGroupWidget;
class CMainPageContentWidget;

namespace Ui {
	class CMainPageTabWidget;
}

class CMainPageTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMainPageTabWidget(QWidget *parent = 0);
    ~CMainPageTabWidget();
    
    // 连接到内容页面
    void connectToChatContent(CMainPageContentWidget* content);

signals:
    void pageChanged(int index);  // 添加页面切换信号

private slots:
    void onTabButtonClicked();

private:
    void createTabButtons();

private:
    Ui::CMainPageTabWidget* ui;
    CChatButton* m_currentButton;  // 当前选中的按钮
    CChatGroupWidget* m_chatGroup; // 聊天组页面
};

#endif // CMAINPAGETABWIDGET_1_H 