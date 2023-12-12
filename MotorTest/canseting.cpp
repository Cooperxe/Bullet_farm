#include "canseting.h"
#include "ui_canseting.h"

Canseting::Canseting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canseting)
{
    ui->setupUi(this);
//    this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);//焦点

}

Canseting::~Canseting()
{
    delete ui;
}

void Canseting::on_pushButton_clicked()//打开设置
{
    this->hide();
}


void Canseting::on_pushButton_2_clicked()//关闭设置
{
    this->hide();
}

