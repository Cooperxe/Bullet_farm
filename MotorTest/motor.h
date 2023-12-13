#ifndef MOTOR_H
#define MOTOR_H

#include <QWidget>

namespace Ui {
class motor;
}

class motor : public QWidget
{
    Q_OBJECT

public:
    explicit motor(QWidget *parent = nullptr);
    ~motor();

private:
    Ui::motor *ui;
};

#endif // MOTOR_H
