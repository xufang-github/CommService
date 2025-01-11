//utf-8 文件
#include "CSettingsWidget.h"
#include "ui_CSettingsWidget.h"
#include <QSettings>
#include <QMessageBox>
#include "CBAClient/comm/CCommClient.h"

#define SettingFile "CBAClient.ini"

CSettingsWidget::CSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CSettingsWidget())
{
    ui->setupUi(this);
    setupConnections();
    loadSettings();
}

CSettingsWidget::~CSettingsWidget()
{
    delete ui;
}

void CSettingsWidget::setupConnections()
{
    connect(ui->saveBtn, &QPushButton::clicked, this, &CSettingsWidget::onSaveSettings);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &CSettingsWidget::onCancelSettings);
    connect(ui->backBtn, &QPushButton::clicked, this, [this]() { emit backClicked(); });
}

void CSettingsWidget::loadSettings()
{
    QSettings settings(SettingFile, QSettings::IniFormat);
    m_originalIp = settings.value("ip", "123.249.105.160").toString();
    m_originalPort = settings.value("port", 8080).toUInt();
    
    ui->ipEdit->setText(m_originalIp);
    ui->portEdit->setText(QString::number(m_originalPort));
}

void CSettingsWidget::onSaveSettings()
{
    QString ip = ui->ipEdit->text().trimmed();
    QString portStr = ui->portEdit->text().trimmed();
    
    if (ip.isEmpty() || portStr.isEmpty()) {
        QMessageBox::warning(this, tr("错误"), tr("IP和端口号不能为空"));
        return;
    }
    
    bool ok;
    int port = portStr.toInt(&ok);
    if (!ok || port <= 0 || port > 65535) {
        QMessageBox::warning(this, tr("错误"), tr("端口号必须在1-65535之间"));
        return;
    }
    
    QSettings settings(SettingFile, QSettings::IniFormat);
    settings.setValue("ip", ip);
    settings.setValue("port", port);
    settings.sync();
    
    // 重新连接服务器
    CCommClient::instance()->connectToServer(ip, port);
    
    QMessageBox::information(this, tr("提示"), tr("设置已保存"));
    emit backClicked();  // 返回登录页面
}

void CSettingsWidget::onCancelSettings()
{
    // 恢复原始设置
    ui->ipEdit->setText(m_originalIp);
    ui->portEdit->setText(QString::number(m_originalPort));
    emit backClicked();  // 返回登录页面
} 