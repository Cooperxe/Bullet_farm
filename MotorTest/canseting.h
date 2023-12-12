#ifndef CANSETING_H
#define CANSETING_H

#include <QWidget>

namespace Ui {
class Canseting;
}

class Canseting : public QWidget
{
    Q_OBJECT

public:
    explicit Canseting(QWidget *parent = nullptr);
    ~Canseting();
    int CANtype;//CAN卡类型
    int index;//索引号
    int baundRate;//波特率
    int devicCOM;//端口号

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Canseting *ui;
};

#endif // CANSETING_H
