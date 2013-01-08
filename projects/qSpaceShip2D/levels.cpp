#include "game2d.h"


#define ENEMY_TIME_MAX 40
#define ENEMY_COUNT_MAX 20
#define ENEMY_FALL_STEP 15 //~h/40


int enemy_time=0;
int enemy_count=0;

void
Game2D::
initEnemy (){
    enemy_time=0;
    enemy_count=0;

    evec_.erase (evec_.begin(), evec_.end());

    int size=DEFAULT_UNIT_SIZE;
    int y=0;

    switch (level()){
        case 5:
        setMovable (1);
        case 1: genLevel1 (size, 0); break;

        case 6:
        setMovable (1);
        case 2:{
            genLevel2 (size, 0); break;
        }break;

        case 3:{
            genLevel3 (size, 0);
        }break;

        case 4:{
            setMovable (1);
            genLevel4 (size, 0);
        }break;

        case 7:{
            genLevel7 (size, 0); break;
        }break;

        case 12:
        setMovable (1);
        case 8: genLevel1 (size, 1); break;

        case 13:
        setMovable (1);
        case 9: genLevel2 (size, 1); break;

        case 10: genLevel3 (size, 1); break;

        case 11:{
            setMovable (1);
            genLevel4 (size, 1);
        }break;

        case 14:{
            genLevel7 (size, 1); break;
        }break;
    }
}

void
Game2D::
genLevel1 (int size, int var){
    int y=120;
    int type=0;

    if (var) type=2;
    addEnemyLine (0, y, size, 8, type, 0);

    if (var) type=1;
    y+=size;
    addEnemyLine (0, y, size, 8, type, 1);

    if (var) type=0;
    y+=size;
    addEnemyLine (0, y, size, 8, type, 2);
}

void
Game2D::
genLevel2 (int size, int var){
    int y=120;
    int type=0;

    if (var) type=0;
    addEnemyLine (0, y, size, 2, type, 1);

    if (var) type=1;
    y+=size;
    addEnemyLine (0, y, size, 4, type, 1);

    if (var) type=2;
    y+=size;
    addEnemyLine (0, y, size, 6, type, 1);

    if (var) type=1;
    y+=size;
    addEnemyLine (0, y, size, 4, type, 1);

    if (var) type=0;
    y+=size;
    addEnemyLine (0, y, size, 2, type, 1);

    if (var) type=2;
    y+=size*2;
    addEnemyLine (0, y, size, 10, type, 1);
}

void
Game2D::
genLevel3 (int size, int var){
    int y=20+myrand (0, 100);
    int type=0;

    for (int i=0; i<10; i++){
        if (var) type=myrand (0, 3);
        addEnemyLine (0, y, size, myrand (2, 10), type, myrand (0, 3));
        y+=size;
    }
}

void
Game2D::
genLevel4 (int size, int var){
    setMovable (1);
    size = myrand (20, 40);
    int y=0;
    int type=0;
    while (enemy_count < ENEMY_COUNT_MAX){
        size = myrand (20, 40);
        y-=size;
        if (var) type=myrand (0, 3);
        addEnemy (myrand (0, width ()-size), y, size, type);
        ++enemy_count;
    }
}

void
Game2D::
genLevel7 (int size, int var){
    setMovable (1);
    size = myrand (20, 40);
    int y=0;
    int type=0;
    while (enemy_count < ENEMY_COUNT_MAX*3){
        size = myrand (20, 40);
        int new_enemy=myrand (1, 8);
        y-=size;
        if (var) type=myrand (0, 3);
        addEnemyLine (0, y, size, new_enemy, type, myrand (0, 3));
        enemy_count+=new_enemy;
    }
}

void
Game2D::
moveEnemy (){
    if (!enemy_time){
        for (int i=0; i<evec_.size (); i++){
            int y=evec_[i].y();
            if (y < height () - evec_[i].size () -1) evec_[i].setY(y+ENEMY_FALL_STEP);
            else{
                evec_[i].setY(y-height () + 1);
            }
        }
        enemy_time=ENEMY_TIME_MAX;
    }
    else --enemy_time;
}
