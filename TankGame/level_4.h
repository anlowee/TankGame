#ifndef LEVEL_4_H
#define LEVEL_4_H

#include <QWidget>

namespace Ui {
class level_4;
}

class level_4 : public QWidget
{
    Q_OBJECT

public:
    explicit level_4(QWidget *parent = nullptr);
    ~level_4();

private:
    Ui::level_4 *ui;
};

#endif // LEVEL_4_H
