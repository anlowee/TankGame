#ifndef NUMBER_5_H
#define NUMBER_5_H

#include <QWidget>

namespace Ui {
class number_5;
}

class number_5 : public QWidget
{
    Q_OBJECT

public:
    explicit number_5(QWidget *parent = nullptr);
    ~number_5();

private:
    Ui::number_5 *ui;
};

#endif // NUMBER_5_H
