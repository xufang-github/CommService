//utf-8 文件
#ifndef CChatButton_H
#define CChatButton_H

#include <QWidget>
#include <QColor>

namespace Ui {
	class CChatButton;
}

class CChatButton : public QWidget
{
    Q_OBJECT
public:
   CChatButton(QWidget* parent = 0);
   CChatButton(const QString& txt,QWidget *parent = 0);
   ~CChatButton();
    void click();
    void setChecked(bool checked);
    // 设置文本
    void setText(const QString& txt);
    // 设置选中时的图片资源和颜色
    void setCheckedStyle(const QString& imgPath, const QColor& color);
    // 设置未选中时的图片资源和颜色
    void setUnCheckedStyle(const QString& imgPath, const QColor& color);

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
	Ui::CChatButton* ui;
    bool m_checked;
    QString m_checkedImgPath;
    QColor m_checkedColor;
    QString m_unCheckedImgPath;
    QColor m_unCheckedColor;
};

#endif // CChatButton_H 