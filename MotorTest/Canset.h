#ifndef CANSET_H
#define CANSET_H

#include <QMainWindow>
#include "ui_Canset.h"
#include "canthread.h"
#include "ControlCAN.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QTime>



class QMenuBar;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddDataToList(QStringList strList);
private slots:
    void onGetProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel,unsigned int channel);
    void onBoardInfo(VCI_BOARD_INFO vbi);
    void on_pushButton_clicked();
    void on_cleanListBtn_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    CANThread *canthread;
};

#endif // CANSET_H
