//utf-8 文件
#ifndef CMAINPAGECONTENTWIDGET_H
#define CMAINPAGECONTENTWIDGET_H

#include <QWidget>
#include <QStackedWidget>

class CMainPageContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMainPageContentWidget(QWidget *parent = nullptr);
    void addPage(QWidget *page, const QString &title);   //添加页面
    void setCurrentIndex(int index);   //设置当前页面索引
    int currentIndex() const;   //获取当前页面索引
    ~CMainPageContentWidget();   //析构函数

private:
    QStackedWidget *m_stackedWidget;   //页面堆栈
};

#endif // CMAINPAGECONTENTWIDGET_H
    