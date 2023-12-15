#ifndef MOTOR_H
#define MOTOR_H

#include <QGroupBox>
#include <QCheckBox>
#include <QTimer>
#include<QElapsedTimer>
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


private slots:
    void Make_Curve_Time();
    void Make_Curve();
    void Dog_Time();

private:
    Ui::motor *ui;

    bool Dateing = false; //数据是否在线// 1秒检查一次
    bool Curve_Mdel = true; //曲线可拖拽

    QTimer dataTimer;
    QTimer dog;

#define Graph_num_motor 8
    float dateView[Graph_num_motor];
    QStringList GraphName={"输入转速","输出转速","电压","电流","功率","电调温度","电机温度","定位角度"};
    QColor colorline[Graph_num_motor] ={"red","blue","green","pink","Yellow","LightGray","Cyan","Magenta"};
    QString GraphUnit[Graph_num_motor]={"Krpm/min","Krpm/min","V","A","W","℃","℃","℃"};
    QCheckBox *CheckBox[Graph_num_motor];

};

#endif // MOTOR_H
