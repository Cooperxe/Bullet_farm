#include "motor.h"
#include "ui_motor.h"

extern MotorStrut MotorCurrentdate[Motor_Num];
extern bool Motor_State[Motor_Num];

motor::motor(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::motor)
{
    ui->setupUi(this);
    Make_Curve();
    dog.start(1500);

}

motor::~motor()
{
    delete ui;
}


void motor::Make_Curve()
{
    for (quint8 i=0;i<Graph_num_motor;i++) {
        CheckBox[i] =new QCheckBox(this);
        CheckBox[i]->setChecked(true);
        CheckBox[i]->setText(GraphName[i]);
        ui->verticalLayout->addWidget(CheckBox[i]);
        connect(CheckBox[i], SIGNAL(clicked(bool)),this,SLOT(checkbox_clicked(bool)));
    }

    ui->Motorqcustomplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QPen pen0[Graph_num_motor];

    for (quint8  i =0;i<Graph_num_motor;i++)
    {
        dateView[i] = 0;
        pen0[i].setWidth(2);//曲线的粗细
        pen0[i].setColor(colorline[i]);//蓝

        ui->Motorqcustomplot->addGraph();

        ui->Motorqcustomplot->graph(i)->setPen(pen0[i]);
        ui->Motorqcustomplot->graph(i)->rescaleKeyAxis();
        ui->Motorqcustomplot->graph(i)->setName(GraphName[i]+QString("：")+QString::number(dateView[i])+GraphUnit[i]);
    }

    // 设置图例
    ui->Motorqcustomplot->legend->setVisible(true); // 显示图例
    ui->Motorqcustomplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignRight | Qt::AlignTop); // 图例放置在右上角

    // 缩小图例
    ui->Motorqcustomplot->legend->setBrush(QBrush(Qt::transparent));

    ui->Motorqcustomplot->legend->setMaximumSize(50, 50); // 设置图例的最大尺寸
    QFont legendFont = font(); // 获取当前字体
    legendFont.setPointSize(8); // 设置图例字体大小
    ui->Motorqcustomplot->legend->setFont(legendFont);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->Motorqcustomplot->xAxis->setTicker(timeTicker);

    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(Make_Curve_Time()));
    connect(&dog, SIGNAL(timeout()), this, SLOT(Dog_Time()));
}

void motor::Dog_Time(){
    if(Motor_State[this->MotorNumber]==true){
        Dateing=true;
        dataTimer.start(0);
        timer.start();

        ui->statusbotton->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background: green;color : yellow");
        ui->statusbotton->setText(QString::number(this->MotorNumber+1)+"号\n在线");
        Motor_State[this->MotorNumber]=false;

        return ;
    }
    Dateing=false;
    dataTimer.stop();
    ui->statusbotton->setText(QString::number(this->MotorNumber+1)+"号\n离线");
    ui->statusbotton->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background: red;color :White");
}

void motor::Make_Curve_Time()
{
    double key = timer.elapsed() / 1000.0; // 计算自启动以来的总秒数
    static double lastPointKey = 0;
    quint8 ii=0;
    if (key-lastPointKey > 0.002) // at most add point every 2 ms
    {
        //第一帧"输入电压","输入电流","输出电流","电调温度"
        //第二帧  "转速输入","转速输出","电机温度","定位角度",
        if(this->Dateing){
            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[0].date16))/10;ii++;
            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[1].date16))/10;ii++;
            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[2].date16))/10;ii++;
            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[3].date16))-200;ii++;

            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[1].date[0].date16))/1000;ii++;
            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[1].date[1].date16))/1000;ii++;
            dateView[ii]=(date16change(MotorCurrentdate[MotorNumber].frame[1].date[2].date16))-200;ii++;
            dateView[ii]=(date16change(MotorCurrentdate[MotorNumber].frame[1].date[3].date16));ii++;


        }else{for(quint8 k=0;k<Graph_num_motor;k++){dateView[k]=0;}}

        for (quint8 i =0;i<Graph_num_motor;i++) {
            ui->Motorqcustomplot->graph(i)->addData(key,dateView[i]);
            ui->Motorqcustomplot->graph(i)->setName(GraphName[i]+QString("：")+QString::number(dateView[i])+GraphUnit[i]);
        }

        lastPointKey = key;
        if(Curve_Mdel)
        {
            for (quint8 i =0;i<Graph_num_motor;i++) {
                ui->Motorqcustomplot->graph(i)->rescaleAxes(true);
            }
            ui->Motorqcustomplot->xAxis->setRange(key+3, 15, Qt::AlignRight);
        }
    }
    qDebug() << "Motor 0 Frame 0 Date 0: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[0].date16)) / 10;
    qDebug() << "Motor 0 Frame 0 Date 1: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[1].date16)) / 10;
    qDebug() << "Motor 0 Frame 0 Date 2: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[2].date16)) / 10;
    qDebug() << "Motor 0 Frame 0 Date 3: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[3].date16)) - 200;
    qDebug() << "Motor 0 Frame 1 Date 0: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[1].date[0].date16)) / 1000;
    qDebug() << "Motor 0 Frame 1 Date 1: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[1].date[1].date16)) / 1000;
    qDebug() << "Motor 0 Frame 1 Date 2: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[1].date[2].date16)) - 200;
    qDebug() << "Motor 0 Frame 1 Date 3: " << (float)(date16change(MotorCurrentdate[MotorNumber].frame[1].date[3].date16));

    ui->Motorqcustomplot->replot();
}

void motor::on_pushButton_clicked()
{
    quint16 chargeValue[4];

    QString textValue = ui->lineEdit->text(); // 获取lineEdit中的文本值
    chargeValue[0] = textValue.toUInt(); // 将文本值转换为quint16

    QString textValue3 = ui->lineEdit_3->text(); // 获取lineEdit中的文本值
    chargeValue[2] = textValue3.toUInt(); // 将文本值转换为quint1

    qDebug() << "Charge in hexadecimal:" << QString("0x%1").arg(chargeValue[0], 0, 16);
    qDebug() << "Charge in hexadecimal:" << QString("0x%1").arg(chargeValue[2], 0, 16);

    emit dischage_chage(0X10000100|(this->MotorNumber&0x000000FF),chargeValue, true);
}


void motor::on_pushButton_2_clicked()
{
    quint16 chargeValue[4];
    QString textValue = ui->lineEdit_2->text(); // 获取lineEdit中的文本值
    chargeValue[0] = textValue.toUInt(); // 将文本值转换为quint16

    quint16 motornum = ((this->MotorNumber)<<8);

    qDebug() << "Charge in hexadecimal:" << QString("0x%1").arg(chargeValue[0], 0, 16);
    qDebug()<<"motornum:"<<motornum;
    emit dischage_chage(0X1000F0FF | motornum, chargeValue, true);

}
