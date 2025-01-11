//utf-8 文件
#include "CPersonalInfoWidget.h"
#include "CBAClient/comm/CCommClient.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QGroupBox>

CPersonalInfoWidget::CPersonalInfoWidget(QWidget *parent)
    : QWidget(parent)
    , m_editMode(false)
{
    setupUI();
    updateUserInfo();
}

CPersonalInfoWidget::~CPersonalInfoWidget()
{
    // 清理资源
}

void CPersonalInfoWidget::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // 创建个人信息组
    QGroupBox* infoGroup = new QGroupBox(tr("个人信息"), this);
    QFormLayout* formLayout = new QFormLayout(infoGroup);
    
    // 用户名
    m_nameEdit = new QLineEdit(this);
    formLayout->addRow(tr("用户名:"), m_nameEdit);
    
    // 邮箱
    m_emailEdit = new QLineEdit(this);
    formLayout->addRow(tr("邮箱:"), m_emailEdit);
    
    // 电话
    m_phoneEdit = new QLineEdit(this);
    formLayout->addRow(tr("电话:"), m_phoneEdit);
    
    mainLayout->addWidget(infoGroup);
    
    // 按钮布局
    QHBoxLayout* btnLayout = new QHBoxLayout();
    
    m_editBtn = new QPushButton(tr("编辑"), this);
    connect(m_editBtn, &QPushButton::clicked, this, &CPersonalInfoWidget::onEditInfo);
    btnLayout->addWidget(m_editBtn);
    
    m_saveBtn = new QPushButton(tr("保存"), this);
    connect(m_saveBtn, &QPushButton::clicked, this, &CPersonalInfoWidget::onSaveInfo);
    btnLayout->addWidget(m_saveBtn);
    
    mainLayout->addLayout(btnLayout);
    
    // 初始状态为非编辑模式
    setEditMode(false);
}

void CPersonalInfoWidget::updateUserInfo()
{
    // TODO: 从服务器获取用户信息
    m_nameEdit->setText(CCommClient::instance()->currentUser().userName);
    m_emailEdit->setText("");
    m_phoneEdit->setText("");
}

void CPersonalInfoWidget::onEditInfo()
{
    setEditMode(true);
}

void CPersonalInfoWidget::onSaveInfo()
{
    // TODO: 保存用户信息到服务器
    setEditMode(false);
}

void CPersonalInfoWidget::setEditMode(bool edit)
{
    m_editMode = edit;
    m_nameEdit->setReadOnly(!edit);
    m_emailEdit->setReadOnly(!edit);
    m_phoneEdit->setReadOnly(!edit);
    m_editBtn->setVisible(!edit);
    m_saveBtn->setVisible(edit);
} 