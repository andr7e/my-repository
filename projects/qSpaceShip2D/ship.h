#ifndef SHIP_H
#define SHIP_H

#include "unit.h"

#define DEFAULT_LASER_LEN 100

class Ship : public Unit{
    bool fire_;
    int len_;

public:
    Ship () : Unit (), fire_(0), len_(DEFAULT_LASER_LEN){

    }

    ~Ship (){

    }

    bool fire () const { return fire_; }
    void setFire (bool f){ fire_=f; }

    bool len () const { return len_; }
    void setLen (int l){ len_=l; }

    void drawFire (QPainter &p, int direct);
    void getFireRect (QRect &rc, int direct);

    virtual void draw (QPainter &p, int direction);

    virtual void timer (int direct, int field_w, int field_h);
};

#endif // SHIP_H
