#include "mycoin.h"
#include "QDebug"
Mycoin::Mycoin(QWidget *parent) : QPushButton(parent)
{

}

Mycoin::Mycoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load (btnImg);
    if(!ret)
    {
        QString str = QString("图片%1加载失败").arg (btnImg);
        qDebug()<<str;
    }
    this->setFixedSize (pix.width (),pix.height ());
    this->setStyleSheet ("QPushButton{border:0px;}");
    this->setIcon (pix);
    this->setIconSize (QSize(pix.width (),pix.height ()));
    //初始化
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //检测反转 正面 -> 反面
    connect (timer1,&QTimer::timeout,[=]{
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        //按钮样式
        this->setFixedSize (pix.width (),pix.height ());
        this->setStyleSheet ("QPushButton{border:0px};");
        this->setIcon (pix);
        this->setIconSize (QSize(pix.width (),pix.height ()));
        if(this->min>this->max)
        {
            min = 1;
            timer1->stop ();
            isAnimation = false;
        }
    });
    //检测反转 正面 -> 反面
    connect (timer2,&QTimer::timeout,[=]{
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        //按钮样式
        this->setFixedSize (pix.width (),pix.height ());
        this->setStyleSheet ("QPushButton{border:0px};");
        this->setIcon (pix);
        this->setIconSize (QSize(pix.width (),pix.height ()));
        if(this->min>this->max)
        {
            max = 8;
            timer2->stop ();
            isAnimation = false;
        }
    });
}

void Mycoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start (30);
        isAnimation = true;
        this->flag = false;
    }
    else
    {
        timer2->start (30);
        isAnimation = true;
        this->flag = true;
    }
}

bool Mycoin::isWin = false;
void Mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent (e);
    }
}
