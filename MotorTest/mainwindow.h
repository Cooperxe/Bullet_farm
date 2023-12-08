#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


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

private slots:
    void openCanSetWindow();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;

    QAction *setCAN_action ;


};

#endif // MAINWINDOW_H
