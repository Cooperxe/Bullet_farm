#include "motor.h"
#include "ui_motor.h"

motor::motor(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::motor)
{
    ui->setupUi(this);
}

motor::~motor()
{
    delete ui;
}


void motor::Make_Curve()
{

}
