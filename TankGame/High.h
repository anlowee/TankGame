#ifndef HIGH_H
#define HIGH_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QPixmap>
#include<QString>
#include<QStackedWidget>
#include "level_1.h"
#include "level_2.h"
#include "level_3.h"
#include "level_4.h"
#include "level_5.h"
#include "number_1.h"
#include "number_2.h"
#include "number_3.h"
#include "number_4.h"
#include "number_5.h"
namespace Ui {
class High;
}

class High : public QWidget
{
    Q_OBJECT

public:
    explicit High(QWidget *parent = nullptr);
    ~High();
private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::High *ui;
    level_1 *a1;
    level_2 *a2;
    level_3 *a3;
    level_4 *a4;
    level_5 *a5;
    number_1 *b1;
    number_2 *b2;
    number_3 *b3;
    number_4 *b4;
    number_5 *b5;
};

#endif // HIGH_H
