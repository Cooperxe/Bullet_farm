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
      CANtype = 4;//ui->baundRate->currentIndex();
      index = ui->comboBox_2->currentIndex();
      baundRate = (int)ui->comboBox_3->currentText().remove("Kbps").toFloat();
      devicCOM = ui->comboBox_4->currentIndex();

      qDebug() << "CAN type:" << CANtype;
      qDebug() << "Index:" << index;
      qDebug() << "Baud Rate:" << baundRate;
      qDebug() << "Device COM:" << devicCOM;
      this->hide();
}


void Canseting::on_pushButton_2_clicked()//关闭设置
{
    this->hide();
}

