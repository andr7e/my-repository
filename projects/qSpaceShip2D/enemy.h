#ifndef ENEMY_H
#define ENEMY_H

#include "unit.h"

class Enemy : public Unit{
public:
    virtual void draw (QPainter &p, int direction=0){
        int w=width();
        int h=height();
        int a=255*health ()/maxHealth ();

        switch (type()){
            case 0:{
                p.setBrush(QColor (255, 200, 0, a));
            }break;

            case 1:{
                p.setBrush(QColor (255, 100, 0, a));
            }break;

            case 2:{
                p.setBrush(QColor (255, 0, 0, a));
            }break;
        }

        p.setPen(Qt::white);

        p.drawRect (x(), y(), w, h);
    }
};

#endif // ENEMY_H
