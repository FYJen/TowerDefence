/*
 * Cannon cpp.
 */

#include <iostream>
#include <vector>
#include <map>
#include "resources/cannon.h"
#include "resources/cannon_ball.h"
#include "resources/config.h"
#include "resources/window.h"

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

Cannon::Cannon(XInfo &xinfo, int castelTopWall, int castelRightWall) : 
        castelTopWall(castelTopWall), castelRightWall(castelRightWall) {
    // Default all motions to false.
    rotateUp = false;
    rotateDown = false;
    moveForward = false;
    moveBackward = false;

    // Set movement speed.
    moveSpeed = CANNON_MOVE_SPEED;

    // Set diameter for the wheels.
    diameter = (xinfo.height / SCREEN_TO_CANNON) / 3;

    // Cannon's holder.
    holderHeight = xinfo.height / SCREEN_TO_CANNON;
    holderWidth = xinfo.width / SCREEN_TO_CANNON;
    holderX = castelRightWall - (castelRightWall / 7);
    holderY = castelTopWall - (diameter / 2) - holderHeight;

    // Cannon wheels.
    int segementOfWidth = holderWidth / 3;
    frontWheelX = holderX - segementOfWidth;
    frontWheelY = castelTopWall - diameter;
    backWheelX = frontWheelX - segementOfWidth - (diameter / 2);
    backWheelY = castelTopWall - diameter;

    // Cannon tube.
    tubeX = holderX - (holderWidth / 2);
    tubeY = holderY + (holderHeight / 5);
    tubeWidth = holderWidth;
    tubeHeight = holderHeight / 3;

}

void Cannon::paint(XInfo &xinfo) {
    // Draw all the cannon balls that have been shot out.
    for(int i = 0; i < cannonBallVec.size(); ++i) {
        cannonBallVec[i]->paint(xinfo);
    }

    // Draw cannon tube.
    XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], tubeX, tubeY,
                   tubeWidth, tubeHeight);

    // Draw cannon holder.
    {
        XPoint points[] = {
                {holderX, holderY},
                {holderX, holderY + holderHeight},
                {holderX - holderWidth, holderY + holderHeight},
                {holderX, holderY}
            };
        int npoints = sizeof(points)/sizeof(XPoint);

        XFillPolygon(xinfo.display, xinfo.pixmap, xinfo.gc[1], points,
                     npoints, Complex, CoordModeOrigin);
        XDrawLines(xinfo.display, xinfo.pixmap, xinfo.gc[0], points,
                   npoints, CoordModeOrigin);
    }

    // Draw wheels.
    XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc[0], frontWheelX,
             frontWheelY, diameter, diameter, 0, 360*64);
    XFillArc(xinfo.display, xinfo.pixmap, xinfo.gc[0], backWheelX,
             backWheelY, diameter, diameter, 0, 360*64);
}

void Cannon::move() {
    if (rotateUp) cout << "Move cannon up" << endl;
    if (rotateDown) cout << "Move cannon down" << endl;
    
    if (moveForward) {
        if (frontWheelX + diameter + moveSpeed >= castelRightWall) {
            int difference = castelRightWall - (diameter + frontWheelX);
            
            holderX += difference;
            tubeX += difference;
            frontWheelX += difference;
            backWheelX += difference;
        } else {
            holderX += moveSpeed;
            tubeX += moveSpeed;
            frontWheelX += moveSpeed;
            backWheelX += moveSpeed;
        }
    }
    
    if (moveBackward) {
        if (holderX - holderWidth - moveSpeed <= 0) {
            int difference = holderX - holderWidth;

            holderX -= difference;
            tubeX -= difference;
            frontWheelX -= difference;
            backWheelX -= difference;
        } else {
            holderX -= moveSpeed;
            tubeX -= moveSpeed;
            frontWheelX -= moveSpeed;
            backWheelX -= moveSpeed;
        }
    }
}

void Cannon::fire() {
    int ballX = tubeX + tubeWidth;
    int ballY = tubeY + (tubeHeight / 4);
    int ballDiameter = tubeHeight / 2 ;
    float angle = 0.0;
    cannonBallVec.push_back(new CannonBall(ballX, ballY, ballDiameter, angle));
}

void Cannon::updateOrRemoveCannonBalls(XInfo &xinfo) {
    for (int i = 0; i < cannonBallVec.size(); ++i) {
        if (cannonBallVec[i]->shouldBeRemoved()) {
            delete cannonBallVec[i];
            cannonBallVec.erase(cannonBallVec.begin() + i);
        } else {
            cannonBallVec[i]->updatePosition(xinfo);
        }
    }
}

vector<CannonBall *> Cannon::getCannonBalls() {
    return cannonBallVec;
}

void Cannon::setRotateUp(bool value) {
    rotateUp = value;
}

void Cannon::setRotateDown(bool value) {
    rotateDown = value;
}

void Cannon::setMoveForward(bool value) {
    moveForward = value;
}

void Cannon::setMoveBackward(bool value) {
    moveBackward = value;
}

bool Cannon::isRotateUp() {
    return rotateUp;
}

bool Cannon::isRotateDown() {
    return rotateDown;
}

bool Cannon::isMoveForward() {
    return moveForward;
}

bool Cannon::isMoveBackward() {
    return moveBackward;
}
