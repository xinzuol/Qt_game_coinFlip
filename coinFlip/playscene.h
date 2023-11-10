#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mypushbutton.h>
#include <QPainter>
#include "mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = 0);
    PlayScene(int chooseNum);
    void paintEvent (QPaintEvent *event);
signals:
    void backSignals ();
public slots:
private:
    int levelNum;
    int gameLevel[4][4];
    Mycoin *coinArray[4][4];
};

#endif // PLAYSCENE_H
