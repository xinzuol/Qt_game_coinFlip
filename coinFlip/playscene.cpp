#include "playscene.h"
#include "QDebug"
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include "dataconfig.h"
#include <numeric>
#include <functional>
#include <QPropertyAnimation>
#include <QSound>
PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}

PlayScene::PlayScene(int chooseNum)
{
    this->levelNum = chooseNum;
    //基本设置
    this->setFixedSize (320,588);
    this->setWindowIcon (QIcon(":/res/Coin0001.png"));
    this->setWindowTitle (QString("第%1关").arg (chooseNum));
    //菜单栏
    QMenuBar *bar = menuBar ();
    setMenuBar (bar);
    //菜单
    QMenu *statrMenu = bar->addMenu ("main");
    QAction * exitAction = statrMenu->addAction("EXIT");
    statrMenu->addSeparator ();
    QAction * helpAction = statrMenu->addAction ("帮助");
    //退出
    connect(exitAction,&QAction::triggered,this,&close);
    //音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound * flipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound * winSound = new QSound(":/res/LevelWinSound.wav",this);
    //返回按键
    MyPushButton *back = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    back->setParent (this);
    back->move (this->width ()-back->width (),this->height ()-back->height ());
    //返回实现
    connect (back,&MyPushButton::clicked,this,[=]{
        //点击音乐
        backSound->play ();
        QTimer::singleShot (200,this,[=]{
            emit this ->backSignals ();
        });
    });
    //设置标签
    QLabel *label = new QLabel;
    label->setParent (this);
    label->setFixedSize (150,30);
    //设置字体
    QFont font;
    font.setFamily ("华文新魏");
    font.setPointSize (20);
    QString str = QString("Level: %1").arg (this->levelNum);
    //字体连接标签
    //    label->setFont (font);
    label->setFont (QFont("华文新魏",20));
    label->setText (str);
    label->setGeometry (30,this->height ()-50,120,50);
    //胜利图片
    QLabel* winLabel = new QLabel(this);
    QPixmap pix(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry ((this->width ()-pix.width ())*0.5,-pix.height (),pix.width (),pix.height ());
    winLabel->setStyleSheet ("QPushButton{border:0px;}");
    winLabel->setPixmap (pix);
    //显示金币背景图
    Mycoin::isWin = false;
    for(int i=0;i<4;i++)
        for(int j =0;j<4;j++)
        {
            QLabel *labelback = new QLabel;
            labelback->setGeometry (0,0,50,50);
            labelback->setPixmap (QPixmap(":/res/BoardNode(1).png"));
            labelback->setParent (this);
            labelback->move (57+i*50,200+j*50);
            labelback->setAlignment (Qt::AlignHCenter | Qt::AlignVCenter);
            //二维数组读取数据
            dataConfig config;
            for(int i = 0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    gameLevel[i][j] = config.mData[this->levelNum][i][j];
                }
            }
            //显示金币图案
            QString levelStr = QString(":/res/Coin000%1.png").arg (config.mData[this->levelNum][i][j]);
            Mycoin *coin = new Mycoin(levelStr);
            coin->setParent (labelback);
            //                coin->move (59+i*50,204+j*50);
            coin->move (2,3);
            //属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = config.mData[this->levelNum][i][j];
            //维护金币对象
            coinArray[i][j] = coin;
            //点击事件
            connect (coin,&Mycoin::clicked,this,[=]{

                flipSound->play ();
                coin->changeFlag ();
                gameLevel[i][j]=!gameLevel[i][j];
                //反转附近金币
                QTimer::singleShot (60,this,[=]{
                    //右侧
                    if(coin->posX+1<4)
                    {
                        coinArray[coin->posX+1][coin->posY]->changeFlag ();
                        gameLevel[i+1][j] = !gameLevel[i+1][j];
                    }
                    //左侧
                    if(coin->posX-1>=0)
                    {
                        coinArray[coin->posX-1][coin->posY]->changeFlag ();
                        gameLevel[i-1][j]=!gameLevel[i-1][j];
                    }
                    //上
                    if(coin->posY-1>=0)
                    {
                        coinArray[coin->posX][coin->posY-1]->changeFlag ();
                        gameLevel[i][j-1]=!gameLevel[i][j-1];
                    }
                    //下
                    if(coin->posY+1<4)
                    {
                        coinArray[coin->posX][coin->posY+1]->changeFlag ();
                        gameLevel[i][j+1]=!gameLevel[i][j+1];
                    }
                    //判断胜利
                    int win= 0;
                    for(int k=0;k<sizeof(gameLevel)/sizeof(int);k++)
                    {
                        win+= gameLevel[k/4][k%4];
                    }
                    qDebug()<<win;
                    //胜利取消按钮
                    if(win==16)
                    {
                        Mycoin::isWin = true;
                        //                        winSound->setLoops (-1);
                        winSound->play ();
                        //弹出胜利图片
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration (1000);//动画时间
                        //设置曲线
                        animation->setStartValue (QRect(winLabel->x (),winLabel->y (),winLabel->width (),winLabel->height ()));
                        animation->setEndValue (QRect(winLabel->x (),winLabel->y ()+130,winLabel->width (),winLabel->height ()));
                        animation->setEasingCurve (QEasingCurve::OutBounce);
                        animation->start ();
                    }
                });
            });
        }
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap (0,0,this->width (),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled (pix.width()*0.5,pix.height ()*0.5);
    painter.drawPixmap (10,30,pix.width (),pix.height(),pix);

}
