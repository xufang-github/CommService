//utf8文件 
#ifndef _CMainPageWidget_H_
#define _CMainPageWidget_H_

#include <QWidget>
#include  <QHBoxLayout>

class  CMainPageTabWidget;
class CMainPageContentWidget;
//登录之后的主界面
// 主要显示一些信息，包括：

class  CMainPageWidget : public QWidget
{
	Q_OBJECT
public:

	enum ELayoutType			
	{
		// 未初始化
		E_LAYOUT_NONE,
		//手机布局
		E_LAYOUT_PHONE,
		//平板布局
		E_LAYOUT_PAD
	};
	CMainPageWidget(QWidget *parent = 0);
	~CMainPageWidget();
protected:
	void resizeEvent(QResizeEvent* e) override;
	void showEvent(QShowEvent* e) override;
private:
	void adjustLayout();
	ELayoutType calLayoutType();
private:
	QHBoxLayout* m_pMainLayout;
	CMainPageTabWidget* m_pTabWidget;
	CMainPageContentWidget* m_pContentWidget;
	ELayoutType m_eLayoutType;
	// 0:tab页  1:内容页
	int m_nCurrentIndex;
};

#endif // !_CMainPageWidget_H_
