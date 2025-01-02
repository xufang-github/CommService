//utf8文件 
#ifndef _CBALoginWidget_H_
#define _CBALoginWidget_H_

#include <QMainWindow>

namespace Ui {
	class CBALoginWidget;
}

class  CBALoginWidget : public QMainWindow
{
	Q_OBJECT
public:
	CBALoginWidget(QWidget *parent = 0);
	~CBALoginWidget();
private slots:
	void slotLogin(bool success);
private:
	Ui::CBALoginWidget *ui;
};

#endif // !_CBALoginWidget_H_
