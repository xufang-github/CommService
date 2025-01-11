//utf8文件 
#ifndef _CBAMainWindow_H_
#define _CBAMainWindow_H_

#include <QMainWindow>

// 前向声明
class CBALoginWidget;
class CMainPageWidget;
class CSettingsWidget;

namespace Ui {
	class CBAMainWidget;
}
// 声明CBAMainWidget类
class  CBAMainWidget : public QMainWindow
{
	Q_OBJECT
public:
	CBAMainWidget(QWidget *parent = 0);
	~CBAMainWidget();
private slots:
	void slotLogin(bool success);
	void slotLogout();
	void slotShowSettings();
	void slotHideSettings();
private:
	Ui::CBAMainWidget *ui;
};

#endif // !_CBAMainWindow_H_
