#ifndef NUMBER_4_H
#define NUMBER_4_H

#include <QWidget>

namespace Ui {
class number_4;
}

class number_4 : public QWidget
{
    Q_OBJECT

public:
    explicit number_4(QWidget *parent = nullptr);
    ~number_4();

private:
    Ui::number_4 *ui;
};

#endif // NUMBER_4_H
