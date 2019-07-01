#ifndef FAST_1_H
#define FAST_1_H

#include <QWidget>

namespace Ui {
class Fast_1;
}

class Fast_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Fast_1(QWidget *parent = nullptr);
    ~Fast_1();

private:
    Ui::Fast_1 *ui;
};

#endif // FAST_1_H
