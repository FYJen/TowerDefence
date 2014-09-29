/*
 * Cannon Ball cpp
 */

#include <iostream>
#include <map>
#include <math.h>
#include "resources/cannon_ball.h"
#include "resources/config.h"
#include "resources/window.h"

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

CannonBall::CannonBall(int x, int y, int diameter, float angle) :
        x(x), y(y), diameter(diameter), angle(angle) {
    initVelocity = CANNON_BALL_INIT_VELOCITY;
    attackPower = CANNON_BALL_ATTACK_POWER;
    flyingTime = 1;
    isOnTheGround = false;
    hasHitEnemy = false;
}

void CannonBall::paint(XInfo &xinfo) {
    XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc[0], x, y, diameter,
             diameter, 0, 360*64);
}

void CannonBall::setHasHitEnemy() {
    hasHitEnemy = true;
}

int CannonBall::getAttackPower() {
    return attackPower;
}

bool CannonBall::shouldBeRemoved() {
    return (isOnTheGround or hasHitEnemy);
}

void CannonBall::updatePosition(XInfo &xinfo) {
    if (y == xinfo.height - diameter) {
        isOnTheGround = true;
    }

    if (!isOnTheGround) {
        flyingTime += 0.1;
        x = x + cos(angle) * initVelocity * (flyingTime + 6);
        y = y + (sin(angle) * initVelocity * flyingTime) +
            (0.05 * GRAVITY * flyingTime * flyingTime);
    
        if (y + diameter >= xinfo.height) {
            y = xinfo.height - diameter;
        }
    }
}

int CannonBall::getX() {
    return x;
}

int CannonBall::getY() {
    return y;
}

int CannonBall::getDiameter() {
    return diameter;
}
