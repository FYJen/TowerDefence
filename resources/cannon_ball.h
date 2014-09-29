/*
 * Cannon Ball header file.
 */

#ifndef CANNON_BALL_H
#define CANNON_BALL_H

#include "window.h"

class CannonBall {
    public:
        CannonBall(int x, int y, int diameter, float angle);
        void paint(XInfo &xinfo);
        void updatePosition(XInfo &xinfo);
        void setHasHitEnemy();
        bool shouldBeRemoved();
        int getX();
        int getY();
        int getDiameter();
        int getAttackPower();

    private:
        int x;
        int y;
        int diameter;
        int initVelocity;
        bool isOnTheGround;
        bool hasHitEnemy;
        float angle;
        float flyingTime;
        int attackPower;
};

#endif