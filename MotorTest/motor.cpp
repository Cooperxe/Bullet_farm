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
//    connect(&dog, SIGNAL(timeout()), this, SLOT(Dog_Time()));
    dataTimer.start(20);
    timer.start();
}


void motor::Dog_Time(){
//        if(Motor_State[this->MotorNumber]==true){
//            Dateing=true;
//            dataTimer.start(0);

//            ui->statusbotton->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background: green;color : yellow");
//            ui->statusbotton->setText(QString::number(this->MotorNumber+1)+"号\n在线");
//            Motor_State[this->MotorNumber]=false;

//            return ;
//        }
//        Dateing=false;
//        dataTimer.stop();
//        ui->statusbotton->setText(QString::number(this->MotorNumber+1)+"号\n离线");
//        ui->statusbotton->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background: red;color :White");
                dataTimer.start(20);

}

void motor::Make_Curve_Time()
{

    double key = timer.elapsed() / 1000.0;
        static double lastPointKey = 0;


        if (key - lastPointKey > 0.02) {
        qDebug() << "Time:" << key - lastPointKey;
        ui->Motorqcustomplot->graph(0)->addData(key, 1);
        ui->Motorqcustomplot->xAxis->setRange(key + 3, 8, Qt::AlignRight);
        lastPointKey = key;

        }
}



//void motor::Dog_Time(){
//    if(Motor_State[this->MotorNumber]==true){
//        Dateing=true;
//        dataTimer.start(0);

//        ui->statusbotton->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background: green;color : yellow");
//        ui->statusbotton->setText(QString::number(this->MotorNumber+1)+"号\n在线");
//        Motor_State[this->MotorNumber]=false;

//        return ;
//    }
//    Dateing=false;
//    dataTimer.stop();
//    ui->statusbotton->setText(QString::number(this->MotorNumber+1)+"号\n离线");
//    ui->statusbotton->setStyleSheet("border:2px groove gray;border-radius:4px;padding:2px 4px;background: red;color :White");


//}

//void motor::Make_Curve_Time()
//{
//    static QElapsedTimer timer;

//    QDateTime currentDateTime = QDateTime::currentDateTime();
//    double key1 = currentDateTime.time().hour() * 3600 + currentDateTime.time().minute() * 60 + currentDateTime.time().second(); // time elapsed since start of demo, in seconds
//    double key = timer.elapsed() / 1000.0 + key1; // 计算自启动以来的总秒数

//    static double lastPointKey = 0;
//    quint8 ii=0;
//    if (key-lastPointKey > 0.002) // at most add point every 2 ms
//    {
//        //曲线顺序"输入转速","输出转速","电压","电流","功率","电调温度","电机温度","定位角度"

//        //第一帧"转速","电压","电流","功率","电调温度"
//        //第二帧  "油门输入"，"电机温度",
//        //第三帧"油门输出"，"MCU温度"
//        if(this->Dateing){
//            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[2].date16))/1000;ii++;
//            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[0].date16))/10;ii++;
//            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[1].date16))/10;ii++;
//            dateView[ii]=(dateView[2]*dateView[1]);ii++;

//            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[0].date[3].date16))-200;ii++;
//            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[1].date[1].date16))-200;ii++;
//            dateView[ii]=(float)(date16change(MotorCurrentdate[MotorNumber].frame[2].date[1].date16))-200;ii++;

//            dateView[ii]=(date16change(MotorCurrentdate[MotorNumber].frame[1].date[0].date16));ii++;
//            dateView[ii]=(date16change(MotorCurrentdate[MotorNumber].frame[2].date[0].date16));ii++;
//        }else{for(quint8 k=0;k<Graph_num_motor;k++){dateView[k]=0;}}



//        for (quint8 i =0;i<Graph_num_motor;i++) {
//            ui->Motorqcustomplot->graph(i)->addData(key,dateView[i]);
//            ui->Motorqcustomplot->graph(i)->setName(GraphName[i]+QString("：")+QString::number(dateView[i])+GraphUnit[i]);
//        }
////        ui->lcdNumber_3->display(dateView[0]);
////        ui->lcdNumber->display(dateView[1]);
////        ui->lcdNumber_2->display(dateView[2]);

//        lastPointKey = key;
//        if(Curve_Mdel)
//        {
//            for (quint8 i =0;i<Graph_num_motor;i++) {
//                ui->Motorqcustomplot->graph(i)->rescaleAxes(true);
//            }

//            ui->Motorqcustomplot->xAxis->setRange(key+3, 15, Qt::AlignRight);
//        }

//    }
//    ui->Motorqcustomplot->replot();
//    //CANThread::sendData();
//}
