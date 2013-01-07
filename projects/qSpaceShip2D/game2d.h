#ifndef GAME2D_H
#define GAME2D_H

#include "ship.h"
#include "enemy.h"

#include <vector>

#define FIRE_TIME_MAX 5

#define DEFAULT_SPEED_DELAY 30

int myrand (int min, int max);

class Game2D : public QWidget
{
    //Q_OBJECT

private:
    int state_;
    int score_;
    int level_;
    int time_;
    int direction_;
    int delay_;
    bool pause_;

    int timer_id_;

    Ship ship_;
    std::vector <Enemy> evec_;

public:
    explicit Game2D(QWidget *parent = 0);
        
    int state () const { return state_;}
    int score () const { return score_;}
    int level () const { return level_;}
    int time () const { return time_;}
    int direction () const { return direction_;}
    int delay () const { return delay_;}
    bool pause () const { return pause_;}

    void setState (int v){ state_=v;}
    void setScore (int v){ score_=v;}
    void setLevel (int v){ level_=v;}
    void setTime (int v){ time_=v;}
    void setDirection (int v){ direction_=v;}
    void setDelay (int v){ delay_=v;}
    void setPause (){ pause_=!pause_;}

    void incLevel (){ ++level_; }
    void incTime (){ time_+=delay_; }

    void init ();
    void initShip ();
    void initEnemy ();
    void start ();

    void nextLevel (){
        incLevel ();
        start ();
    }

    void prevLevel (){
        --level_;
        start ();
    }

    void addEnemy (int x, int y, int size);
    void addEnemyLine (int x, int y, int size, int count, int align=0);
    void moveEnemy ();

    void drawBackground (QPainter &p);
    void drawLabels (QPainter &p);
    void drawState (QPainter &p);

    void timer();
    void paint(QPainter &p);

    //events
    void paintEvent (QPaintEvent *);
    void timerEvent(QTimerEvent *);
    bool event(QEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *);
    //void keyPressEvent(QKeyEvent *ke);

/*
signals:
    void changeScore (int);

public slots:
*/
    
};

#endif
