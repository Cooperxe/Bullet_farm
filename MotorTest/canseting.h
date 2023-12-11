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

private:
    Ui::Canseting *ui;
};

#endif // CANSETING_H
