#include "ship.h"

void
Ship::
draw (QPainter &p, int direction){

    drawFire (p, direction);

    int w=width();
    int h=height();

    QBrush brush(QColor(255,255,255,100));
    p.setBrush(brush);

    p.drawRect (x(), y(), w, h);

    if (isLoad()){
        switch (direction){
            case 0: {
                p.drawPixmap(x(), y(), *pixmap());
            }break;

            case 1: {
                p.translate(x()+w, y()+h);
                p.rotate(90);
                p.drawPixmap(-w, 0, *pixmap());
            }break;

            case 2: {
                p.translate(x()+w, y()+h);
                p.rotate(180);
                p.drawPixmap(0, 0, *pixmap());
            }break;

            case 3: {
                p.translate(x()+w, y()+h);
                p.rotate(270);
                p.drawPixmap(0, -w, *pixmap ());
            }break;
        }
    }
    else{
        p.setBrush(Qt::green);

        p.drawEllipse(x(), y(), w, h);
    }

    p.resetTransform();
}

void
Ship::timer (int direct, int field_w, int field_h){
    switch (direct){
        case 0: {
            changePosY (-1);
            hitMinY (0);
        }break;

        case 1: {
            changePosX (1);
            hitMaxX (field_w - width());
        }break;

        case 2: {
            changePosY (1);
            hitMaxY (field_h - height());
        }break;

        case 3: {
            changePosX (-1);
            hitMinX (0);
        }break;
    }
}

int getKdirect (int d){
    if (d==1 || d==2) return 1;

    return -1;
}

void
Ship::drawFire (QPainter &p, int direct){
    if (fire_){
        p.setPen(Qt::green);

        QRect rc;
        getFireRect (rc, direct);

        p.drawLine (rc.x(), rc.y(), rc.x()+rc.width(), rc.y()+rc.height());
    }

}

void
Ship::getFireRect (QRect &rc, int direct){
    rc.setX(x()+width()/2); //xc
    rc.setY(y()+height()/2); //yc

    if (direct==1 || direct==3){
        rc.setWidth(getKdirect(direct)*len_);
        rc.setHeight (0);
    }
    else{
        if (direct==0 || direct==2){
            rc.setWidth(0);
            rc.setHeight (getKdirect(direct)*len_);
        }
    }
}
