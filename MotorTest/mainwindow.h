#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canseting.h"
#include "canthread.h"
#include "motor.h"
#include "ControlCAN.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void CANMenu();
    void ModelViewShow();
private slots:
    void CanSetWindow();
    void CanOpenWindow();
    void SendCAN(quint32 ID,quint16 *charge ,bool state);

private:
    Ui::MainWindow *ui;
    bool CANState;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QAction *setCAN_action ;
    QAction *openCAN_action;

    Canseting *CANsetting;
    CANThread *canthread;
};

#endif // MAINWINDOW_H
