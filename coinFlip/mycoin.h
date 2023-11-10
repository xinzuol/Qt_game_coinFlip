#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
class Mycoin : public QPushButton
{
    Q_OBJECT
public:
    explicit Mycoin(QWidget *parent = 0);
    Mycoin(QString btnImg);
    //动画
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 8;

    int posX;
    int posY;
    bool flag;
    //动画运行判断
    bool isAnimation = false;
    void mousePressEvent (QMouseEvent *e);
    static bool isWin;

signals:

public slots:


};

#endif // MYCOIN_H
