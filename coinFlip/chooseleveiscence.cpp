#include "chooseleveiscence.h"
#include <QMenuBar>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QDebug>
#include <QSound>
ChooseLeveIscence::ChooseLeveIscence(QWidget *parent) : QMainWindow(parent)
{
    //��С
    this->setFixedSize (320,588);
    //ͼƬ
    //    this->setWindowIcon (QPixmap(":/res/Coin0001.png"));
    this->setWindowIcon (QIcon(":/res/Coin0001.png"));
    //����
    this->setWindowTitle ("ѡ��ؿ�");
    //�˵���
    QMenuBar *bar = menuBar ();
    setMenuBar (bar);
    //�˵�
    QMenu *statrMenu = bar->addMenu ("main");
    QAction * exitAction = statrMenu->addAction("EXIT");
    statrMenu->addSeparator ();
    QAction * helpAction = statrMenu->addAction ("����");
    //�˳�
    connect(exitAction,&QAction::triggered,this,&close);
    //fanhui
    MyPushButton *back = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    back->setParent (this);
    back->move (this->width ()-back->width (),this->height ()-back->height ());
    //
    connect (back,&MyPushButton::clicked,this,[=]{
        QTimer::singleShot (200,this,[=]{
            emit this ->backSignals ();
        });
    });
    //guanqian
    for(int i = 0;i<20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent (this);
        menuBtn->move (25 + i%4*70,130+i/4*70);
        //
        QLabel * num = new QLabel;
        num->setParent (this);
        num->setFixedSize (menuBtn->width (),menuBtn->height ());
        num->setText (QString::number (i+1));
        num->move (25 + i%4*70,130+i/4*70);
        //
        num->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);
        //
        num->setAttribute (Qt::WA_TransparentForMouseEvents);
        //
        connect (menuBtn,&MyPushButton::clicked,this,[=]{
            QString str = QString("xuyanzewe%1").arg (i);
            qDebug()<<str;
            //
            play = new PlayScene(i+1);
            //
            QSound * chooseSound = new QSound(":/res/TapButtonSound.wav",play);
            chooseSound->play ();
            //���ó���λ��
            play->setGeometry (this->geometry ());
            this ->hide ();
            play->show ();
            //
            connect (play,&PlayScene::backSignals,this,[=]{
                QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);
                backSound->play ();
                //���ó���λ��
                this->setGeometry (play->geometry ());
                play->hide ();
                this->show ();
                delete play;
                play = nullptr;
            });
        });
    }
}
//����
void ChooseLeveIscence::paintEvent (QPaintEvent *)
{
    //���Ҷ���
    QPainter painter(this);
    //������
    //    painter.drawImage (this->width (),this->height (),QImage(":/res/OtherSceneBg.png"));
    QPixmap pix;
    pix.load (":/res/OtherSceneBg.png");
    painter.drawPixmap (0,0,this->width (),this->height (),pix);
    pix.load (":/res/Title.png");
    painter.drawPixmap ((this->width ()-pix.width ())*0.5,30,pix.width (),pix.height (),pix);
}
