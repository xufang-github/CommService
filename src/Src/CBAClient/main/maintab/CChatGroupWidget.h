//utf-8 文件
#ifndef CMAINPAGETABWIDGET_H
#define CMAINPAGETABWIDGET_H

#include <QWidget>

namespace Ui {
	class CChatGroupWidget;
}

class CChatGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CChatGroupWidget(QWidget *parent = 0);
    ~CChatGroupWidget();
    private:
		Ui::CChatGroupWidget* ui;

};

#endif // CMAINPAGETABWIDGET_H 