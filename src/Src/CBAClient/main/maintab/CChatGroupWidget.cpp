//utf-8 文件
#include "CBAClient/main/maintab/CChatGroupWidget.h"
#include "ui_CChatGroupWidget.h"

CChatGroupWidget::CChatGroupWidget(QWidget *parent) :    
    QWidget(parent),
    ui(new Ui::CChatGroupWidget())
{
    ui->setupUi(this);
}

CChatGroupWidget::~CChatGroupWidget()
{
    delete ui;
}
