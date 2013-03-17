#include <QtGui>
#include "game2d.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
/*
    QWidget pwgt;

    QLabel *nameLabel = new QLabel ("score: ");
    QLabel *scoreLabel = new QLabel;

    Widget w;

    QObject::connect (&w, SIGNAL(changeScore(int)), scoreLabel, SLOT(setNum(int)));

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget (nameLabel);
    hLayout->addWidget (scoreLabel);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(&w);

    pwgt.setLayout(vLayout);

    pwgt.show();
    */
    Game2D w;
    w.setFixedSize(480, 640);
    w.readLevel ();
    w.start ();
    w.show ();
    
    return a.exec();
}
