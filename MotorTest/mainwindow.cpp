#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CANMenu();                                        //CAN设置启动

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

    // 事件
    setCAN_action = new QAction("设置CAN(&N)");
    openCAN_action = new QAction("启动CAN(&O)");
    fileMenu->addAction(setCAN_action);
    fileMenu->addAction(openCAN_action);

    connect(setCAN_action, SIGNAL(triggered()), this, SLOT(CanSetWindow()));
    connect(openCAN_action, SIGNAL(triggered()), this, SLOT(CanOpenWindow()));

    // 颜色
    QString styleSheet =
        "QMenuBar { background-color: white; color: black; }" // 菜单栏背景颜色和文字颜色
        "QMenuBar::item { background-color: white; }" // 菜单栏中的菜单项背景颜色
        "QMenuBar::item:selected { background-color: lightblue; }" // 菜单项悬停时的背景颜色（淡蓝色）
        "QMenu { background-color: white; }" // 菜单背景颜色
        "QMenu::item:selected { background-color: lightblue; }"; // 菜单项悬停时的背景颜色（淡蓝色）

    ui->menubar->setStyleSheet(styleSheet);
    fileMenu->setStyleSheet(styleSheet);
    editMenu->setStyleSheet(styleSheet);
    helpMenu->setStyleSheet(styleSheet);
}

void MainWindow::CanSetWindow()
{
    qDebug("open");
    CANsetting->show(); // 显示新窗口
}

void MainWindow::CanOpenWindow()
{
    qDebug("into CanOpenWindow\r\n");
    if(!CANState)
    {
        qDebug("if CANStatus = 0\r\n");

        canthread->deviceType = CANsetting->CANtype;
        canthread->debicIndex = CANsetting->index;
        canthread->baundRate = CANsetting->baundRate;
        canthread->debicCom = CANsetting->devicCOM;
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


//发送
void MainWindow::SendCAN(quint32 ID,quint16 charge ,bool state){
    this->canthread->dischage_chage_send(ID,charge,state);

}
