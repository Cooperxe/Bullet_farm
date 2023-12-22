#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QDebug>
#include <QPushButton>
#include <QSplitter>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CANMenu();                                        //CAN设置启动
    ModelViewShow();

    this->resize(1200, 470);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setMinimumSize(600, 235); // 可选：设置窗口最小大小

    CANsetting = new Canseting();
    canthread = new CANThread();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CANMenu()
{
    qDebug("tesst");
    fileMenu = ui->menubar->addMenu("CAN启动");
    editMenu = ui->menubar->addMenu("编辑(&E)");
    helpMenu = ui->menubar->addMenu("帮助(&H)");

    // 创建菜单项
    setCAN_action = new QAction("设置CAN(&N)");
    openCAN_action = new QAction("启动CAN(&O)");
    fileMenu->addAction(setCAN_action);
    fileMenu->addAction(openCAN_action);

    // 连接信号和槽
    connect(setCAN_action, SIGNAL(triggered()), this, SLOT(CanSetWindow()));
    connect(openCAN_action, SIGNAL(triggered()), this, SLOT(CanOpenWindow()));

    // 设置样式表
    QString styleSheet =


        "QMenuBar { background-color: rgb(3, 73, 252); color: white; }"
        "QMenuBar::item { background-color: rgb(3, 73, 252); color: white; }"
        "QMenuBar::item:selected { background-color: rgb(192, 192, 192); }"
        "QMenu { background-color: rgb(3, 73, 252); color: white; }"
        "QMenu::item:selected { background-color: rgb(192, 192, 192); }";
    ui->centralwidget->setStyleSheet(styleSheet);
    ui->menubar->setStyleSheet(styleSheet);
    fileMenu->setStyleSheet(styleSheet);
    editMenu->setStyleSheet(styleSheet);
    helpMenu->setStyleSheet(styleSheet);
}


void MainWindow::ModelViewShow()
{
    QSplitter *verticalSplitter = new QSplitter(ui->scrollArea);
    verticalSplitter->setOrientation(Qt::Vertical);
    ui->verticalLayout_3->addWidget(verticalSplitter);

    for (quint16 i = 0; i < Motor_Num; i++) {
        motor *Motor = new motor();

        Motor->MotorNumber = i;
        Motor->setTitle("Motor:" + QString::number(i + 1));

        QSplitter *horizontalSplitter = new QSplitter(Qt::Horizontal);
        horizontalSplitter->addWidget(Motor);

        verticalSplitter->addWidget(horizontalSplitter);

        connect(Motor, SIGNAL(dischage_chage(quint32, quint16 *, bool)), this, SLOT(SendCAN(quint32, quint16*, bool)));
    }
}



//can设置 槽
void MainWindow::CanSetWindow()
{
    qDebug("open");
    CANsetting->show(); // 显示新窗口
}

//can启动 槽
void MainWindow::CanOpenWindow()
{
    if(!CANState)
    {
        qDebug("if CANStatus = 0\r\n");

        canthread->deviceType = CANsetting->CANtype;
        canthread->debicIndex = CANsetting->index;
        canthread->baundRate = CANsetting->baundRate;
        canthread->debicCom = CANsetting->devicCOM;

        qDebug() << "Device Type: " << canthread->deviceType;
        qDebug() << "Debic Index: " << canthread->debicIndex;
        qDebug() << "Baund Rate: " << canthread->baundRate;
        qDebug() << "Debic Com: " << canthread->debicCom;

        bool dev = canthread->openDevice();
        if(dev == true) {
            canthread->start();
            CANState=true;
            this->setCAN_action->setEnabled(false);
            this->openCAN_action->setText("关闭CAN(&O)");
        }
        qDebug()<< "MainWindow->openCAN";
    }
    else
    {
        qDebug("if CANStatus = 1\r\n");

        this->setCAN_action->setEnabled(true);
        this->openCAN_action->setText("启动CAN(&O)");
        canthread->stop();
        canthread->closeDevice();
        CANState=false ;
        qDebug()<< "MainWindow->closeCAN";
    }
}


//发送 槽
void MainWindow::SendCAN(quint32 ID,quint16 * charge ,bool state){
    this->canthread->dischage_chage_send(ID,charge,state);

}
