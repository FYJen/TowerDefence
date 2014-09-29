/*
 * castel header file.
 */
#ifndef CASTEL_H
#define CASTEL_H

#include "window.h"

class Castel {
    public:
        void paint(XInfo &xinfo);
        void looseLifePoint(int points);
        void gainLifePoint(int points);
        void upgrade();
        void setSize(int x, int y, int width, int height);
        int getLifePoints();
        int getCastelLevel();
        int getRightWall();
        int getTopwall();
        Castel(int x, int y, int width, int height);

    private:
        int x;
        int y;
        int width;
        int height;
        int lifePoints;
        int castelLevel;
};

#endif
