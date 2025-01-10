//utf8文件 
#ifndef _CBASettingWidget_H_
#define _CBASettingWidget_H_

#include <QWidget>

namespace Ui {
	class CBASettingWidget;
}

class  CBASettingWidget : public QWidget
{
	Q_OBJECT
public:
	CBASettingWidget(QWidget *parent = 0);
	~CBASettingWidget();
private slots:
	void slotLogin(bool success);
private:
	Ui::CBASettingWidget *ui;
};

#endif // !_CBASettingWidget_H_
