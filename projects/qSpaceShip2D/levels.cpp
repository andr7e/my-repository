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
        case 1:{
            y=120;
            addEnemyLine (0, y, size, 8);

            y+=size;
            addEnemyLine (0, y, size, 8, 1);

            y+=size;
            addEnemyLine (0, y, size, 8, 2);
        }break;

        case 6:
        case 2:{
            y=120;
            addEnemyLine (0, y, size, 2, 1);

            y+=size;
            addEnemyLine (0, y, size, 4, 1);

            y+=size;
            addEnemyLine (0, y, size, 6, 1);

            y+=size;
            addEnemyLine (0, y, size, 4, 1);

            y+=size;
            addEnemyLine (0, y, size, 2, 1);

            y+=size*2;
            addEnemyLine (0, y, size, 10, 1);
        }break;

        case 3:{
            y=20+myrand (0, 100);

            for (int i=0; i<10; i++){
                addEnemyLine (0, y, size, myrand (2, 10), myrand (0, 3));
                y+=size;
            }
        }break;

        case 4:{
            int size = myrand (20, 40);
            int y=0;
            while (enemy_count < ENEMY_COUNT_MAX){
                size = myrand (20, 40);
                y-=size;
                addEnemy (myrand (0, width ()-size), y, size);
                ++enemy_count;
            }
        }break;

        case 7:{
            int size = myrand (20, 40);
            int y=0;
            while (enemy_count < ENEMY_COUNT_MAX*3){
                size = myrand (20, 40);
                int new_enemy=myrand (1, 8);
                y-=size;
                addEnemyLine (0, y, size, new_enemy, myrand (0, 3));
                enemy_count+=new_enemy;
            }
        }break;
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
