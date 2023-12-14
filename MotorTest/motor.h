#ifndef MOTOR_H
#define MOTOR_H

#include <QGroupBox>

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
};

#endif // MOTOR_H
