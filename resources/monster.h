/*
 * Monster header file.
 */
#ifndef MONSTER_H
#define MONSTER_H

#include "castel.h"
#include "window.h"

class Monster {
    public:
        Monster(int x, int y, int width, int height);
        void paint(XInfo &xinfo);
        void move(Castel *castel);
        void setSize(int x, int y, int width, int height);
        void looseLifePoints(int points);
        int getLifePoints();
        int getReward();
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        void setHasReachedTheWall();
        bool hasReachedTheWall();

    private:
        int x;
        int y;
        int width;
        int height;
        int lifePoints;
        int attackPower;
        int moveSpeed;
        bool reachedTheWall;
        int goldAwardedAfterKill;
};

#endif
