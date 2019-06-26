#ifndef NUMBER_1_H
#define NUMBER_1_H

#include <QWidget>

namespace Ui {
class number_1;
}

class number_1 : public QWidget
{
    Q_OBJECT

public:
    explicit number_1(QWidget *parent = nullptr);
    ~number_1();

private:
    Ui::number_1 *ui;
};

#endif // NUMBER_1_H
