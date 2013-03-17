
#include "game2d.h"

Game2D::Game2D(QWidget *parent) : QWidget(parent), state_(0), score_(0), level_(1), direction_(0), delay_(0), pause_(0), movable_(0), timer_id_(0)
{

}

void
Game2D::
init (){
    state_=0;
    score_=0;
    time_=0;
    direction_=0;
    movable_=0;

    delay_=DEFAULT_SPEED_DELAY;

    if (!bg_.isLoad ()){
        bg_.loadImage ("bg.png");
    }

    killTimer (timer_id_);
    timer_id_=startTimer (delay_);
}

void
Game2D::
initShip (){
    ship_.setFire (0);
    ship_.setHealth(100);
    ship_.setMaxHealth(100);

    if (!ship_.isLoad ()){
        ship_.loadImage ("ship.png");
        ship_.scale (4, 3);
    }

    ship_.setX((width() - ship_.width ())/2);
    ship_.setY(height() - ship_.height ());

    ship_.setDamage (10);

    /*
    //////////////tuning 2
    ship_.setDamage (20);
    ship_.setFireLenght (50);
    ship_.setStep (1);

    //////////////tuning 3
    ship_.setDamage (10);
    ship_.setLen (120);
    ship_.setStep (2);
    */

    /*//////////////tuning 4
    ship_.setDamage (5);
    ship_.setFireLenght (50);
    ship_.setStep (1);
    ship_.setFireWidth (20);*/

    /*
    ship_.setDamage (100);
    ship_.setFireLenght (200);
    ship_.setStep (2);
    ship_.setFireWidth (20);
    */
}

void
Game2D::
addEnemy (int x, int y, int size, int type){
    Enemy enemy;
    enemy.setX(x);
    enemy.setY(y);
    enemy.setSize (size);

    enemy.setType (type);

    switch (type){
        case 0:{
            enemy.setHealth(100);
            enemy.setMaxHealth(100);
        }break;

        case 1:{
            enemy.setHealth(300);
            enemy.setMaxHealth(300);
        }break;

        case 2:{
            enemy.setHealth(500);
            enemy.setMaxHealth(500);
        }break;

        case 3:{
            enemy.setHealth(1000);
            enemy.setMaxHealth(1000);
        }break;

        case 4:{
            enemy.setHealth(2000);
            enemy.setMaxHealth(2000);
        }break;

        case 5:{
            enemy.setHealth(3000);
            enemy.setMaxHealth(3000);
        }break;

        case 6:{
            enemy.setHealth(4000);
            enemy.setMaxHealth(4000);
        }break;
    }

    evec_.push_back(enemy);
}

void
Game2D::
addEnemyLine (int x, int y, int size, int count, int type, int align){
    if (align==1) x=x+width()/2-size*count/2;
    if (align==2) x=x+width()-size*count;

    for (int i=0; i<count; i++){
        addEnemy (x, y, size, type);
        x+=size;
    }
}

void
Game2D::
start (){
    init ();

    initShip ();

    initEnemy ();
}

void Game2D::drawBackground (QPainter &p){
    if (!bg_.isLoad ()){
        p.setBrush(Qt::black);
        p.drawRect(0, 0, width(), height ());
    }
    else bg_.draw (p);
}

void Game2D::drawLabels (QPainter &p){

    QFont font;
    font.setPixelSize(18);
    p.setFont(font);

    p.setPen (Qt::white);

    QString text;
    text.sprintf ("level: %d score: %d enemy: %d", level(), score (), evec_.size ());
    p.drawText(0, 0, width(), height (), Qt::AlignLeft, text);

    ////////////////
    int sec=time_/1000;
    int msec=time_%1000;
    int min=sec/60;
    sec=sec%60;

    text.sprintf ("%02d:%02d.%03d", min, sec, msec);
    p.drawText(0, 0, width(), height (), Qt::AlignRight, "time: " + text);
}

void Game2D::drawState (QPainter &p){
    if (state_!=1 || pause ()){
        QFont font;
        font.setPixelSize(50);
        p.setFont(font);

        p.setPen (Qt::white);

        QString str;
        if (!pause()){
            if (state_==0) str="START";
            else str="Game over";
        }else str="PAUSE";
        p.drawText(0, 0, width(), height(), Qt::AlignCenter, str);
    }
}

void Game2D::paint(QPainter &p){

    drawBackground (p);

    for (std::size_t i=0; i<evec_.size(); i++) drawUnit (evec_[i], p);//evec_[i].draw (p);

    if (state_==2) ship_.setType(1);
    else ship_.setType(0);

    drawUnit (ship_, p, direction_);

    drawLabels (p);

    drawState (p);

    /*
    typedef QSharedPointer <Unit> spUnit;
    QVector < spUnit>  units;

    Ship ship;
    Enemy e;

    units.push_back((spUnit)new Ship());
    //units.push_back((spUnit)&e);

    for (int i=0; i<units.size(); i++) drawUnit (*units[i].data(), p);

    */
}

void Game2D::paintEvent(QPaintEvent *){
    QPainter p (this);
    paint (p);
}

bool Game2D::event(QEvent *event){
     //qDebug () << event->type();

     if (event->type() == QEvent::KeyPress) {
         QKeyEvent *ke = static_cast<QKeyEvent *>(event);

         if (!state_) state_=1;
         else{
             if (state_==2) start ();
         }

         switch (ke->key()){
             case Qt::Key_Up:
             case Qt::Key_W: direction_=UP; break;

             case Qt::Key_Right:
             case Qt::Key_D: direction_=RIGHT; break;

             case Qt::Key_Down:
             case Qt::Key_S: direction_=DOWN; break;

             case Qt::Key_Left:
             case Qt::Key_A: direction_=LEFT; break;

             case Qt::Key_Shift: ship_.setFire(1); break;

             case Qt::Key_Tab: nextLevel (); break;

             case Qt::Key_Backspace: prevLevel (); break;

             case Qt::Key_Pause: setPause (); break;
         }

         return true;
     }

     return QWidget::event(event);
}

void Game2D::mouseDoubleClickEvent(QMouseEvent *)
{
    ship_.setFire(1);
}

void Game2D::mousePressEvent(QMouseEvent *event)
{
    ship_.setFire(1);

    int xc=ship_.x();
    int yc=ship_.y();

    int x=event->x() - xc;
    int y=event->y() - yc;

    if (abs(y) > abs(x)){
        if (y>0) setDirection(DOWN);
        else if (y<0) setDirection(UP);
    }
    else{
        if (x>0) setDirection(RIGHT);
        else if (x<0) setDirection(LEFT);
    }

    //ship_.setX(event->x());
    //ship_.setY(event->y());
}



bool isInInterval (int x, int x1, int x2){
    if (x >= x1 && x < x2) return 1;

    return 0;
}

void Game2D::timer(){
    if (pause()) return;

    if (!evec_.size() && state_==1){
        //if (level () >=2) state_=2;
        //else
        nextLevel ();
    }

    if (state_==1){
        bool destroy=0;

        ship_.onFire();
        ship_.timer(direction_, width (), height ());

        for (int i=0; i<evec_.size(); i++){
            int x1=evec_[i].x ();
            int y1=evec_[i].y ();
            int x2=evec_[i].x () + evec_[i].width();
            int y2=evec_[i].y () + evec_[i].height();

            //ship hit in vertical line
            if (direction_==1 || direction_==3){
                if (isInInterval (ship_.y (), y1, y2) ||
                    isInInterval (ship_.y () + ship_.height()/2, y1, y2) ||
                    isInInterval (ship_.y () + ship_.height(), y1, y2)){

                    if (ship_.x() > x1) destroy=ship_.hitMinX(x2); //right
                    else{
                        if (ship_.x() +  ship_.width () > x1) destroy=ship_.hitMaxX(x1-ship_.width ()); //left
                    }
                }
            }

            //ship hit in horizontal line
            if (direction_==0 || direction_==2){
                if (isInInterval (ship_.x (), x1, x2) ||
                    isInInterval (ship_.x () + ship_.width()/2, x1, x2) ||
                    isInInterval (ship_.x () + ship_.width(), x1, x2)){
                    if (ship_.y() > y1) destroy=ship_.hitMinY(y2); //down
                    else{
                        if (ship_.y() +  ship_.height () > y1) destroy=ship_.hitMaxY(y1-ship_.height ()); //up
                    }
                }
            }

            if (ship_.fire()){

                bool damaged=0;
                QRect rc;
                ship_.getFireRect (rc, direction());
                //in fire axis y
                if (direction_==1 || direction_==3){
                    if (isInInterval (rc.y(), y1, y2) || isInInterval (rc.y()+rc.height(), y1, y2)){
                        //cross fire line & left enemy || //cross fire line & right enemy
                        if ((x1 > rc.x() && x1 < rc.x()+rc.width()) || (x2 < rc.x() && x2 > rc.x()+rc.width())){
                            damaged=1;
                        }
                    }
                }

                if (direction_==0 || direction_==2){
                    if (isInInterval (rc.x(), x1, x2) || isInInterval (rc.x()+rc.width(), x1, x2)){
                        //cross fire line & up enemy || //cross fire line & down enemy
                        if ((y1 > rc.y() && y1 < rc.y()+rc.height()) || (y2 < rc.y() && y2 > rc.y()+rc.height())){
                            damaged=1;
                        }
                    }
                }

                if (damaged){
                    ++score_;
                    evec_[i].addHealth (-(ship_.damage ()));
                    if (evec_[i].health () == 0) evec_.erase (evec_.begin () + i);
                }

            }

            if (destroy){
                state_=2;

                /*ship_.addHealth (-1);
                switch(direction_){
                    case 0: direction_=2; break;
                    case 1: direction_=3; break;
                    case 2: direction_=0; break;
                    case 3: direction_=1; break;
                }

                if (ship_.health () == 0) state_=2;
                */
                /*QMessageBox box;
                box.warning(0,"Game over", "Ship destroyed!", 0, 1);
                box.show();
                */
            }
        }

        incTime ();
        if (movable()) moveEnemy ();
    }
}

void Game2D::timerEvent(QTimerEvent *){

    timer ();

    emit update();
}

#include <fstream>
void Game2D::closeEvent(QCloseEvent *event)
{
    //qDebug () << "close";

    writeLevel ();

    event->accept();
}

void Game2D::writeLevel ()
{
    std::ofstream out (LEVEL_FILE);

    out << level();

    out.close();
}

void Game2D::readLevel ()
{
    std::ifstream in (LEVEL_FILE);

    if (in){
        int level=0;

        in >> level;

        if (level>1) setLevel(level);

        in.close();
    }
}

int myrand (int min, int max){
    return min + ((rand ()/1000) % max);
}
