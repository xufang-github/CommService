//utf-8 文件
#ifndef CCHATGROUPWIDGET_H
#define CCHATGROUPWIDGET_H

#include <QWidget>
#include <QMap>

class QPushButton;

namespace Ui {
	class CChatGroupWidget;
}

class CChatGroupWidget : public QWidget
{
	Q_OBJECT
public:
	explicit CChatGroupWidget(QWidget *parent = nullptr);
	~CChatGroupWidget();

signals:
	void chatGroupSelected(const QString& topic);

private slots:
	void onGroupSelected();
	void onMessageReceived(const QString& topic, const QString& message);

private:
	void initChatGroups();
	void addChatGroup(const QString& name, const QString& topic);

private:
	Ui::CChatGroupWidget* ui;
	QMap<QString, QPushButton*> m_chatGroups;  // topic -> button 映射
};

#endif // CCHATGROUPWIDGET_H 