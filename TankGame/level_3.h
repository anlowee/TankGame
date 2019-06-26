#ifndef LEVEL_3_H
#define LEVEL_3_H

#include <QWidget>

namespace Ui {
class level_3;
}

class level_3 : public QWidget
{
    Q_OBJECT

public:
    explicit level_3(QWidget *parent = nullptr);
    ~level_3();

private:
    Ui::level_3 *ui;
};

#endif // LEVEL_3_H
