//utf-8 文件
#ifndef CMAINPAGETABWIDGET_1_H
#define CMAINPAGETABWIDGET_1_H

#include <QWidget>

namespace Ui {
	class CMainPageTabWidget;
}

class CMainPageTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CMainPageTabWidget(QWidget *parent = 0);
    ~CMainPageTabWidget();
    private:
		Ui::CMainPageTabWidget* ui;

};

#endif // CMAINPAGETABWIDGET_1_H 