#ifndef LEVEL_2_H
#define LEVEL_2_H

#include <QWidget>

namespace Ui {
class level_2;
}

class level_2 : public QWidget
{
    Q_OBJECT

public:
    explicit level_2(QWidget *parent = nullptr);
    ~level_2();

private:
    Ui::level_2 *ui;
};

#endif // LEVEL_2_H
