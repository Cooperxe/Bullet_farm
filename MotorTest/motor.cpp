#include "motor.h"
#include "ui_motor.h"

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
    //    ui->Motorqcustomplot->yAxis->grid()->setPen(QPen(QColor(0, 0, 0), 1));//设置y轴的栅格线的颜色和大小
    //    ui->Motorqcustomplot->xAxis->grid()->setPen(QPen(QColor(0, 0, 0), 1));//设置y轴的栅格线的颜色和大小.
    ui->Motorqcustomplot->legend->setVisible(true);
    //    ui->Motorqcustomplot->legend->setFont(xAxisFont);
    //    ui->Motorqcustomplot->legend->setBrush(QColor(colorbrush,200));
    ui->Motorqcustomplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->Motorqcustomplot->xAxis->setTicker(timeTicker);
}
