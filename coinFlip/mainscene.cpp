#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPixmap>
#include <QAction>
#include <mypushbutton.h>
#include <QPropertyAnimation>
#include <QTimer>
#include <QSound>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize (320,588);
    this->setWindowIcon (QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle ("翻金币");
    //退出实现
    connect (ui->quit,&QAction::triggered,this,&MainScene::close);
    //切换场景
    choose = new ChooseLeveIscence;
    //监听返回信号
    connect (choose,&ChooseLeveIscence::backSignals,this,[=]{
        //设置场景位置
        this->setGeometry (choose->geometry ());
        choose->hide();
        this->show ();
    });
    //开始按钮
    MyPushButton *statBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    statBtn->setParent (this);
    statBtn->move (this->width ()*0.5-statBtn->width ()*0.5,this->height ()*0.7);
    //按钮音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
    //按钮动作
    connect(statBtn,&MyPushButton::clicked,this,[=](){
        statBtn->zoom ();
        startSound->play ();
        QTimer::singleShot (300,this,[=]()
        {
            //设置场景位置细节
            choose->setGeometry (this->geometry ());
            this->hide ();
            choose->show ();
        });

    });
}

MainScene::~MainScene()
{
    delete ui;
}
//界面设置
void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap (0,0,this->width (),this->height (),pix);

    pix.load (":/res/Title.png");
    pix = pix.scaled (pix.width ()*0.5,pix.height ()*0.5);
    painter.drawPixmap (10,30,pix.width (),pix.height (),pix);

}
