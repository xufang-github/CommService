//utf-8 文件
#include "CMainPageTabWidget.h"
#include "ui_CMainPageTabWidget.h"
#include "CBAClient/main/maintab/CChatButton.h"

CMainPageTabWidget::CMainPageTabWidget(QWidget *parent) :    
    QWidget(parent),
    ui(new Ui::CMainPageTabWidget())
{
    ui->setupUi(this);
    {
        CChatButton*  btn = new  CChatButton(ui->widget);
        btn->setCheckedStyle(":/global/chat_checked.png",QColor(255,0,0));
        btn->setUnCheckedStyle(":/global/chat.png",QColor(0,0,0));
        btn->setProperty("tabIndex",0);
        btn->setChecked(true);
        ui->hLayout->addWidget(btn);
    }

    {
        CChatButton*  btn = new  CChatButton(ui->widget);
        btn->setCheckedStyle(":/global/person_checked.png",QColor(255,0,0));
        btn->setUnCheckedStyle(":/global/person.png",QColor(0,0,0));
        btn->setProperty("tabIndex",1);        
        ui->hLayout->addWidget(btn);
    }
  



}

CMainPageTabWidget::~CMainPageTabWidget()
{
    delete ui;
}
