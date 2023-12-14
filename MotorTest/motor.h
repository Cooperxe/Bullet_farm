#ifndef MOTOR_H
#define MOTOR_H

#include <QGroupBox>
#include <QCheckBox>
#include "canthread.h"


namespace Ui {
class motor;
}

class motor : public QGroupBox
{
    Q_OBJECT

public:
    explicit motor(QWidget *parent = nullptr);
    ~motor();

    quint16 MotorNumber;

    void Make_Curve();

private:
    Ui::motor *ui;

#define Graph_num_motor 9
    float dateView[Graph_num_motor];
    QStringList GraphName={"转速","电压","电流","功率","电调温度","电机温度","MCU温度","油门输入","油门输出"};
    QColor colorline[Graph_num_motor] ={"red","blue","green","pink","black","Yellow","LightGray","Cyan","Magenta"};
    QString GraphUnit[Graph_num_motor]={"Krpm/min","V","A","W","℃","℃","℃","num","num"};
    QCheckBox *CheckBox[Graph_num_motor];

};

#endif // MOTOR_H
