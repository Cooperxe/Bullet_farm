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
    CANMenu();
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
    setCAN_action = new QAction("启动设置(&N)");
    fileMenu->addAction(setCAN_action);
    connect(setCAN_action, SIGNAL(triggered()), this, SLOT(openCanSetWindow()));

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

void MainWindow::openCanSetWindow()
{
    qDebug("open");
    Canseting *CansetWidget  = new Canseting();
    CansetWidget->show(); // 显示新窗口
}
