#ifndef LEVEL_1_H
#define LEVEL_1_H

#include <QWidget>

namespace Ui {
class level_1;
}

class level_1 : public QWidget
{
    Q_OBJECT

public:
    explicit level_1(QWidget *parent = nullptr);
    ~level_1();

private:
    Ui::level_1 *ui;
};

#endif // LEVEL_1_H
