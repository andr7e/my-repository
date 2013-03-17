#ifndef SHIP_H
#define SHIP_H

#include "unit.h"

class Ship : public Unit{

public:
    Ship () : Unit (){
    }

    ~Ship (){
    }

    void drawFire (QPainter &p, int direct);
    void getFireRect (QRect &rc, int direct);

    virtual void draw (QPainter &p, int direction);

    virtual void timer (int direct, int field_w, int field_h);
};

#endif // SHIP_H
