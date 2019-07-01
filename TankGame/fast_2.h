#ifndef FAST_2_H
#define FAST_2_H

#include <QWidget>

namespace Ui {
class Fast_2;
}

class Fast_2 : public QWidget
{
    Q_OBJECT

public:
    explicit Fast_2(QWidget *parent = nullptr);
    ~Fast_2();

private:
    Ui::Fast_2 *ui;
};

#endif // FAST_2_H
