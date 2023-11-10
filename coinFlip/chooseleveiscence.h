#ifndef CHOOSELEVEISCENCE_H
#define CHOOSELEVEISCENCE_H

#include <QMainWindow>
#include <QPainter>
#include <playscene.h>
class ChooseLeveIscence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLeveIscence(QWidget *parent = 0);

    void paintEvent (QPaintEvent* );
signals:
    //返回
    void backSignals();
public slots:
private:
    PlayScene * play = nullptr;
};

#endif // CHOOSELEVEISCENCE_H
