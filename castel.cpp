/*
 * Castel cpp.
 */

#include <iostream>
#include <map>
#include "resources/castel.h"
#include "resources/config.h"
#include "resources/window.h"

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

Castel::Castel(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    lifePoints = CASTEL_LIFE_POINTS;
    castelLevel = CASTEL_LEVEL;
}

void Castel::paint(XInfo &xinfo) {
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x, y, width, height);
}

void Castel::looseLifePoint(int points) {
    if (lifePoints - points <= 0) lifePoints = 0;
    else lifePoints -= points;
}

void Castel::gainLifePoint(int points) {
    if (lifePoints + points >= CASTEL_LIFE_POINTS) lifePoints = CASTEL_LIFE_POINTS;
    else lifePoints += points;
}

void Castel::setSize(int x, int y, int width, int height) {
    x = x;
    y = y;
    width = width;
    height = height;
}

void Castel::upgrade() {
    if (castelLevel < MAX_CASTEL_LEVEL) castelLevel += 1;
}

int Castel::getLifePoints() {
    return lifePoints;
}

int Castel::getCastelLevel() {
    return castelLevel;
}

int Castel::getRightWall() {
    return width;
}

int Castel::getTopwall() {
    return y;
}

