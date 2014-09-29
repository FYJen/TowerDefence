/*
 * Monster cpp file.
 */

#include <iostream>
#include <map>
#include "resources/monster.h"
#include "resources/castel.h"
#include "resources/config.h"
#include "resources/window.h"

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

Monster::Monster(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    lifePoints = MONSTER_LIFE_POINTS;
    attackPower = ATTACK_POWER;
    moveSpeed = MONSTER_MOVE_SPEED;
    goldAwardedAfterKill = MONSTER_AWARD_GOLD;
    reachedTheWall = false;
}

void Monster::paint(XInfo &xinfo) {
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x, y, width, height);
}

void Monster::move(Castel *castel) {
    int castelRightWall = castel->getRightWall();
    if (x - moveSpeed > castelRightWall) {
        x -= moveSpeed;
    } else {
        x = castelRightWall;
        setHasReachedTheWall();
        castel->looseLifePoint(attackPower);
        looseLifePoints(lifePoints);
    }
}

void Monster::setSize(int x, int y, int width, int height) {
    x = x;
    y = y;
    width = width;
    height = height;
}

void Monster::looseLifePoints(int points) {
    if (lifePoints - points >= 0) lifePoints -= points;
    else lifePoints = 0;
}

int Monster::getLifePoints() {
    return lifePoints;
}

int Monster::getReward() {
    return goldAwardedAfterKill;
}

void Monster::setHasReachedTheWall() {
    reachedTheWall = true;
}

bool Monster::hasReachedTheWall() {
    return reachedTheWall;
}

int Monster::getX() {
    return x;
}

int Monster::getY() {
    return y;
}

int Monster::getWidth() {
    return width;
}

int Monster::getHeight() {
    return height;
}
