#ifndef DEFENCE_1_H
#define DEFENCE_1_H

#include <QWidget>

namespace Ui {
class Defence_1;
}

class Defence_1 : public QWidget
{
    Q_OBJECT

public:
    explicit Defence_1(QWidget *parent = nullptr);
    ~Defence_1();

private:
    Ui::Defence_1 *ui;
};

#endif // DEFENCE_1_H
