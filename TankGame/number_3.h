#ifndef NUMBER_3_H
#define NUMBER_3_H

#include <QWidget>

namespace Ui {
class number_3;
}

class number_3 : public QWidget
{
    Q_OBJECT

public:
    explicit number_3(QWidget *parent = nullptr);
    ~number_3();

private:
    Ui::number_3 *ui;
};

#endif // NUMBER_3_H
