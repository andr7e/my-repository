#ifndef ENEMY_H
#define ENEMY_H

#include "unit.h"

class Enemy : public Unit{
public:
    virtual void draw (QPainter &p, int direction=0){
        int w=width();
        int h=height();

        p.setBrush(QColor (255, 0, 0, 255*health ()/maxHealth ()));
        p.setPen(Qt::white);

        p.drawRect (x(), y(), w, h);
    }
};

#endif // ENEMY_H
