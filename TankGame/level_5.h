#ifndef LEVEL_5_H
#define LEVEL_5_H

#include <QWidget>

namespace Ui {
class level_5;
}

class level_5 : public QWidget
{
    Q_OBJECT

public:
    explicit level_5(QWidget *parent = nullptr);
    ~level_5();

private:
    Ui::level_5 *ui;
};

#endif // LEVEL_5_H
