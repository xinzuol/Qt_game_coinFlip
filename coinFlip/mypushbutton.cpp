#include "mypushbutton.h"
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load (normalImg);
    if(!ret)
    {
        return;
    }
    //设置固定图片
    this->setFixedSize (pix.width (),pix.height ());
    //不规则图片
    this->setStyleSheet ("QPushButton{border:0px;}");
    //设置图标
    this->setIcon (pix);
    this->setIconSize (QSize(pix.width (),pix.height ()));
}
//延迟跳动
void MyPushButton::zoom()
{  QPropertyAnimation * animation = new  QPropertyAnimation(this,"geometry");
    //
    animation->setDuration (200);
    //
    animation->setStartValue (QRect(this->x (),this->y (),this->width (),this->height ()));
    animation->setStartValue (QRect(this->x (),this->y ()-5,this->width (),this->height ()));
    //
    animation->setEasingCurve (QEasingCurve::OutBounce);
    //
    animation->setDuration (200);
    //
    animation->setStartValue (QRect(this->x (),this->y (),this->width (),this->height ()));
    animation->setStartValue (QRect(this->x (),this->y ()+5,this->width (),this->height ()));
    //
    animation->setEasingCurve (QEasingCurve::OutBounce);
    //
    animation->start ();

}
//按钮切换图片
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!= "")
    {
        QPixmap pix;
        bool ret = pix.load (this->pressImgPath);
        if(!ret)
        {
            return;
        }
        //设置固定图片
        this->setFixedSize (pix.width (),pix.height ());
        //不规则图片
        this->setStyleSheet ("QPushButton{border:0px;}");
        //设置图标
        this->setIcon (pix);
        this->setIconSize (QSize(pix.width (),pix.height ()));
    }
    return QPushButton::mousePressEvent(e);

}
//按钮切换图片
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->normalImgPath!= "")
    {
        QPixmap pix;
        bool ret = pix.load (this->normalImgPath);
        if(!ret)
        {
            return;
        }
        //设置固定图片
        this->setFixedSize (pix.width (),pix.height ());
        //不规则图片
        this->setStyleSheet ("QPushButton{border:0px;}");
        //设置图标
        this->setIcon (pix);
        this->setIconSize (QSize(pix.width (),pix.height ()));
    }
    return QPushButton::mouseReleaseEvent (e);
}
