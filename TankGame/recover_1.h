#ifndef RECOVER_1_H
#define RECOVER_1_H

#include <QWidget>

namespace Ui {
class Recover_1;
}

class Recover_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Recover_1(QWidget *parent = nullptr);
    ~Recover_1();

private:
    Ui::Recover_1 *ui;
};

#endif // RECOVER_1_H
