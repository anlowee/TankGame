#ifndef RECOVER_2_H
#define RECOVER_2_H

#include <QWidget>

namespace Ui {
class Recover_2;
}

class Recover_2 : public QWidget
{
    Q_OBJECT

public:
    explicit Recover_2(QWidget *parent = nullptr);
    ~Recover_2();

private:
    Ui::Recover_2 *ui;
};

#endif // RECOVER_2_H
