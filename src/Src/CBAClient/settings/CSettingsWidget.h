//utf-8 文件
#ifndef CSETTINGSWIDGET_H
#define CSETTINGSWIDGET_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
    class CSettingsWidget;
}

class CSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CSettingsWidget(QWidget *parent = nullptr);
    ~CSettingsWidget();

signals:
    void backClicked();  // 添加返回信号

public slots:
    void onSaveSettings();
    void onCancelSettings();

private:
    void loadSettings();
    void setupConnections();

private:
    Ui::CSettingsWidget* ui;
    QString m_originalIp;
    quint16 m_originalPort;
};

#endif // CSETTINGSWIDGET_H