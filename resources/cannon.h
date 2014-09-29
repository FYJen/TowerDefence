/*
 * Cannon header file
 */

#ifndef CANNON_H
#define CANNON_H

#include <vector>
#include "cannon_ball.h"
#include "window.h"

class Cannon {
    public:
        Cannon(XInfo &xinfo, int castelTopWall, int castelRightWall);
        void paint(XInfo &xinfo);
        void move();
        void fire();
        void updateOrRemoveCannonBalls(XInfo &xinfo);
        vector<CannonBall *> getCannonBalls();

        // Set motion sensors.
        void setRotateUp(bool value);
        void setRotateDown(bool value);
        void setMoveForward(bool value);
        void setMoveBackward(bool value);

        bool isRotateUp();
        bool isRotateDown();
        bool isMoveForward();
        bool isMoveBackward();

    private:
        // Cannon balls.
        vector<CannonBall *> cannonBallVec;

        // Cannon's motions.
        bool rotateUp;
        bool rotateDown;
        bool moveForward;
        bool moveBackward;

        // Cannon's holder.
        int holderX;
        int holderY;
        int holderWidth;
        int holderHeight;

        // Cannon's tube.
        int tubeX;
        int tubeY;
        int tubeWidth;
        int tubeHeight;

        // Cannon's front wheel.
        int frontWheelX;
        int frontWheelY;

        // Cannon's back wheel.
        int backWheelX;
        int backWheelY;

        // Diameter for both wheels.
        int diameter;

        // Cannon speed.
        int moveSpeed;

        // Castel info.
        int castelTopWall; 
        int castelRightWall;
};

#endif