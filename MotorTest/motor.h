#ifndef MOTOR_H
#define MOTOR_H

#include <QGroupBox>
#include <QCheckBox>
#include <QTimer>
#include<QElapsedTimer>
#include "canthread.h"
#include "ControlCAN.h"

namespace Ui {
class motor;
}

class motor : public QGroupBox
{
    Q_OBJECT

public:
    explicit motor(QWidget *parent = nullptr);
    ~motor();
//    quint16 chargeValue[0];
    quint16 MotorNumber;
    Q_SIGNAL
        void dischage_chage(quint32,quint16 * ,bool);



private slots:
    void Make_Curve_Time();
    void Make_Curve();
    void Dog_Time();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::motor *ui;

    bool Dateing = false; //数据是否在线// 1秒检查一次
    bool Curve_Mdel = true; //曲线可拖拽

    QTimer dataTimer;
    QTimer dog;
    QElapsedTimer timer;

#define Graph_num_motor 8
    float dateView[Graph_num_motor];
    QStringList GraphName={"输入电压","输入电流","输出电流","电调温度","转速输入","转速输出","电机温度","定位角度"};
    QColor colorline[Graph_num_motor] ={"red","blue","green","pink","Yellow","LightGray","Cyan","Magenta"};
    QString GraphUnit[Graph_num_motor]={"V","A","A","℃","Krpm/min","Krpm/min","℃","℃"};
    QCheckBox *CheckBox[Graph_num_motor];

};

#endif // MOTOR_H
