//utf8文件 
#ifndef _CBAMainWindow_H_
#define _CBAMainWindow_H_

#include <QMainWindow>

namespace Ui {
	class CBAMainWidget;
}

class  CBAMainWidget : public QMainWindow
{
	Q_OBJECT
public:
	CBAMainWidget(QWidget *parent = 0);
	~CBAMainWidget();
private slots:
	void slotLogin(bool success);
private:
	Ui::CBAMainWidget *ui;
};

#endif // !_CBAMainWindow_H_
