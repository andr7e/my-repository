#ifndef UNIT_H
#define UNIT_H

#include <QtGui>

#define DEFAULT_UNIT_SIZE 30 //~h/20

class Unit{
    int x_;
    int y_;
    int type_;
    int size_;
    int step_;
    bool load_;
    int health_;
    int max_health_;
    QPixmap pixmap_;

public:
    Unit () : x_(0), y_(0), type_(0), size_(DEFAULT_UNIT_SIZE), step_(1), load_(0), health_(1), max_health_(1) {

    }

    void _loadImage (QPixmap &pixmap, const QString &name){
        QFile fd (name);
        if (fd.exists()){
            load_=1;
            pixmap.load(name);
        }
    }

    void loadImage (const QString &name){
        _loadImage  (pixmap_, name);
    }

    QPixmap *pixmap () { return &pixmap_;}
    bool isLoad () const { return load_;}

    void scale (int num, int denum){
        if (load_) pixmap_=(pixmap_.scaledToHeight(pixmap_.height()*num/denum, Qt::SmoothTransformation));
    }

    virtual ~Unit (){

    }

    int x () const { return x_; }
    int y () const { return y_; }

    void setX (int x){ x_=x;}
    void setY (int y){ y_=y;}

    int width () const {
        return (load_) ?  pixmap_.width() : size_;
    }

    int height () const {
        return (load_) ?  pixmap_.height() : size_;
    }

    int step () const { return step_; }
    void setStep (int step) { step_=step; }

    int size () const { return size_; }
    void setSize (int size) { size_=size; }

    int type () const { return type_; }
    void setType (int t){ type_=t; }

    int health () const { return health_; }
    void setHealth (int health) { health_=health; }
    void addHealth (int health) { health_+=health; }

    int maxHealth () const { return max_health_; }
    void setMaxHealth (int health) { max_health_=health; }


    void changePosX (int d){
        x_+=(step_*d);
    }

    void changePosY (int d){
        y_+=(step_*d);
    }

    bool hitMinX (int min){
        if (x_ < min){ x_ = min; return 1; }
        return 0;
    }

    bool hitMaxX (int max){
        if (x_ > max - 1){ x_ = max - 1; return 1; }
        return 0;
    }

    bool hitMinY (int min){
        if (y_ < min){ y_ = min; return 1; }
        return 0;
    }

    bool hitMaxY (int max){
        if (y_ > max - 1){ y_ = max - 1; return 1; }
        return 0;
    }

    virtual void draw (QPainter &p, int direction=0){
        if (!load_){
            p.setBrush(Qt::black);
            p.setPen(Qt::white);

            p.drawRect (x(), y(), width(), height());
        }
        else  p.drawPixmap(x(), y(), pixmap_);
    }

    virtual void timer (int direction, int field_w, int field_h){ }

};

#endif // UNIT_H
