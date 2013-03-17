#include "unit.h"

void drawUnit (Unit &u, QPainter &p, int direction){
    u.draw (p, direction);
}

void
Unit::
scale (int num, int denum){
    if (load_) pixmap_=(pixmap_.scaledToHeight(pixmap_.height()*num/denum, Qt::SmoothTransformation));
}
