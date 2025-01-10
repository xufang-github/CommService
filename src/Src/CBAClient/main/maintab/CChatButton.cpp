//utf-8 文件
#include "CChatButton.h"
#include "ui_CChatButton.h"
#include <QMouseEvent>

CChatButton::CChatButton(QWidget *parent) :    
    ui(new Ui::CChatButton()),
	m_checked(false)
{
    ui->setupUi(this);
	// label 和 pushButton 鼠标事件穿透
	ui->label->setAttribute(Qt::WA_TransparentForMouseEvents);
	ui->pushButton->setAttribute(Qt::WA_TransparentForMouseEvents);

}

void CChatButton::setChecked(bool checked)
{
	m_checked = checked;
	if (m_checked)
	{
		ui->pushButton->setIcon(QIcon(m_checkedImgPath));
		ui->label->setStyleSheet("background-color:" + m_checkedColor.name(QColor::HexRgb) +";");
	}
	else
	{
		ui->pushButton->setIcon(QIcon(m_unCheckedImgPath));
		ui->label->setStyleSheet("background-color:" + m_unCheckedColor.name(QColor::HexRgb) +";");
	}
}

CChatButton::CChatButton(const QString& txt, QWidget* parent):
	QWidget(parent),
	ui(new Ui::CChatButton()),
	m_checked(false)
{
	ui->setupUi(this);
	ui->label->setText(txt);
	// label 和 pushButton 鼠标事件穿透
	ui->label->setAttribute(Qt::WA_TransparentForMouseEvents);
	ui->pushButton->setAttribute(Qt::WA_TransparentForMouseEvents);
}

CChatButton::~CChatButton()
{
    delete ui;
}

 void CChatButton::mouseReleaseEvent(QMouseEvent* event)
 {
	this->setChecked(true);
	emit clicked();
	QWidget::mousePressEvent(event);
 }

 void CChatButton::setCheckedStyle(const QString& checkedImgPath, const QColor& checkedColor)
 {
	m_checkedImgPath = checkedImgPath;
	m_checkedColor = checkedColor;
	setChecked(m_checked);
	
 }


 void CChatButton::setUnCheckedStyle(const QString& imgPath, const QColor& color)
 {
	m_unCheckedImgPath = imgPath;
	m_unCheckedColor = color;
	setChecked(m_checked);
 }			