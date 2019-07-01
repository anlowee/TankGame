#ifndef DEFENCE_2_H
#define DEFENCE_2_H

#include <QWidget>

namespace Ui {
class Defence_2;
}

class Defence_2 : public QWidget
{
    Q_OBJECT

public:
    explicit Defence_2(QWidget *parent = nullptr);
    ~Defence_2();

private:
    Ui::Defence_2 *ui;
};

#endif // DEFENCE_2_H
