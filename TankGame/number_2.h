#ifndef NUMBER_2_H
#define NUMBER_2_H

#include <QWidget>

namespace Ui {
class number_2;
}

class number_2 : public QWidget
{
    Q_OBJECT

public:
    explicit number_2(QWidget *parent = nullptr);
    ~number_2();

private:
    Ui::number_2 *ui;
};

#endif // NUMBER_2_H
