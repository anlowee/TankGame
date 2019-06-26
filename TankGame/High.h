#ifndef HIGH_H
#define HIGH_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QPixmap>
#include<QString>
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
    void on_nextButton1_clicked();
    void on_nextButton2_clicked();
private:
    Ui::High *ui;
    void initPictureList1();
    void initPictureList2();
    QStringList pictureList1;
    QStringList pictureList2;
    int pictureNumber1=1;
    int pictureNumber2=1;
};

#endif // HIGH_H
