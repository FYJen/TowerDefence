/*
 * Environment cpp
 */
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>
#include <map>
#include "resources/environment.h"
#include "resources/monster.h"
#include "resources/castel.h"
#include "resources/cannon.h"
#include "resources/config.h"
#include "resources/window.h"
#include "resources/helper.h"

/*
 * Header files for X functions
 */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

Environment::Environment(XInfo &xInfo) : xInfo(xInfo) {
    money = INITIAL_GOLD;
    lastSpawnTime = 0;
    difficulty = 1;
    setMonsterSpawnTimer(difficulty);
    initCastel();
    initCannon();
    initMonster();
}

void Environment::paintGuideline() {
    int x = xInfo.width / 4;
    int y = xInfo.height / 4;

    // Student Info.
    const char *info = "Name: Fei-Yang Jen, ID: fjen";
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1], x, y,
                info, strlen(info));

    // Instruction.
    const char *line1 = "Use 'Left' and 'Right' arrow keys to control the cannon.";
    const char *line2 = "Use 'Space' key to fire cannon balls.";
    const char *line3 = "Monster will spawn, and you will have to kill them all.";
    const char *line4 = "You will have 100 life points. When it reaches 0, gameover!";
    const char *line5 = "'u' to increase difficulty.'b' to kill all monsters.";
    const char *line6 = "Press ENTER to start the game!";
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1], x, y + 50,
                line1, strlen(line1));
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1], x, y + 100,
                line2, strlen(line2));
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1], x, y + 150,
                line3, strlen(line3));
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1], x, y + 200,
                line4, strlen(line4));
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1], x, y + 250,
                line5, strlen(line5));
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1], x, y + 300,
                line6, strlen(line6));

    //Copy buffer to window.
    XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc[1],
        0, 0, xInfo.width, xInfo.height,  // region of pixmap to copy
        0, 0); // position to put top left corner of pixmap in window

    XFlush(xInfo.display);
}

void Environment::paintGameOver() {
    int x = xInfo.width / 3;
    int y = xInfo.height / 3;

    const char *gameOver = "Game Over!";
    const char *line1 = "Press ENTER to close.";
    XDrawString(xInfo.display, xInfo.window, xInfo.gc[0], x, y,
                gameOver, strlen(gameOver));
    XDrawString(xInfo.display, xInfo.window, xInfo.gc[0], x, y + 50,
                line1, strlen(line1));

    XFlush(xInfo.display);
}

void Environment::paint() {
    // Draw into the buffer
    XFillRectangle(xInfo.display, xInfo.pixmap, xInfo.gc[1], 0, 0, xInfo.width,
                   xInfo.height);
    
    // Draw castel, cannon, cannon_balls and monsters.
    castel->paint(xInfo);
    cannon->paint(xInfo);
    for(int i = 0; i < monstersVec.size(); ++i) {
        monstersVec[i]->paint(xInfo);
    }

    //Draw score board.
    char textBox[BufferSize];
    sprintf(textBox, "Money: %d   Difficulty: %d   Castel Health: %d", money,
            difficulty, castel->getLifePoints());
    XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[0], 15, 25, textBox,
                strlen(textBox));

    //Copy buffer to window.
    XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc[1], 
        0, 0, xInfo.width, xInfo.height,  // region of pixmap to copy
        0, 0); // position to put top left corner of pixmap in window

    XFlush(xInfo.display);
}

bool Environment::hasGameEnded() {
    if(castel->getLifePoints() == 0) return true;
    else return false;
}

void Environment::gameEnds() {
    vector<CannonBall *> cannonBallVec = cannon->getCannonBalls();
    for(int i = 0; i < cannonBallVec.size(); ++i) {
        delete cannonBallVec[i];
    }
    delete cannon;

    for(int i = 0; i < monstersVec.size(); ++i) {
        delete monstersVec[i];
    }

    delete castel;
}

void Environment::killAllMonsters() {
    for (int i = 0; i < monstersVec.size(); ++i) {
        monstersVec[i]->looseLifePoints(monstersVec[i]->getLifePoints());
    }
}

void Environment::addMoney(int gold) {
    money += gold;
}

void Environment::addMonster() {
    time_t curTime = time(NULL);
    if (lastSpawnTime != (int)curTime && (int)curTime % spawnTimer == 0) {
        int height = xInfo.height / SCREEN_TO_MONSTER;
        int width = height / 2;
        int y = xInfo.height - height;
        int x = xInfo.width;

        monstersVec.push_back(new Monster(x, y, width, height));
        lastSpawnTime = curTime;
    }
}

void Environment::removeMonsters() {
    for (int i = 0; i < monstersVec.size(); ++i) {
        if (monstersVec[i]->getLifePoints() == 0) {
            if(!monstersVec[i]->hasReachedTheWall()) {
                addMoney(monstersVec[i]->getReward());
            }
            delete monstersVec[i];
            monstersVec.erase(monstersVec.begin() + i);
        }
    }
}

void Environment::setMonsterSpawnTimer(int level) {
    if (level == 1) spawnTimer = MONSTER_SPAWN_TIME_LVL1;
    else if (level == 2) spawnTimer = MONSTER_SPAWN_TIME_LVL2;
    else spawnTimer = MONSTER_SPAWN_TIME_LVL3;
}

void Environment::initCastel() {
    int height = xInfo.height / SCREEN_TO_CASTEL;
    int width = height; // A square castel.
    int y = xInfo.height - height;
    int x = 2;

    castel = new Castel(x, y, width, height);
}

void Environment::initCannon() {
    cannon = new Cannon(xInfo, castel->getTopwall(), castel->getRightWall());
}

void Environment::initMonster() {
    addMonster();
}

XInfo &Environment::getXInfo() {
    return xInfo;
}

void Environment::setIsMouseInside(bool value) {
    isInsideScreen = value;
}

bool Environment::isMouseInside() {
    return isInsideScreen;
}

void Environment::increaseDifficulity() {
    if (difficulty + 1 <= MAX_DIFFICULITY) difficulty += 1;
    else difficulty = MAX_DIFFICULITY;

    setMonsterSpawnTimer(difficulty);
}

void Environment::checkObjectCollision() {
    vector<CannonBall *> cannonBallVec = cannon->getCannonBalls();
    for (int i = 0; i < cannonBallVec.size(); ++ i) {
        for (int j = 0; j < monstersVec.size(); ++j ){
            int ballX = cannonBallVec[i]->getX();
            int ballY = cannonBallVec[i]->getY();
            int ballDiameter = cannonBallVec[i]->getDiameter();
            int monsterX = monstersVec[j]->getX();
            int monsterY = monstersVec[j]->getY();
            int monsterWidth = monstersVec[j]->getWidth();
            int monsterHeight = monstersVec[j]->getHeight();

            if (ballY + ballDiameter >= monsterY && ballX + ballDiameter >= monsterX
                && ballX + ballDiameter <= monsterX + monsterWidth) {
                cannonBallVec[i]->setHasHitEnemy();
                monstersVec[j]->looseLifePoints(cannonBallVec[i]->getAttackPower());
                break;
            }

            if (ballY + ballDiameter >= monsterY && ballX >= monsterX &&
                ballX <= monsterX + monsterWidth) {
                cannonBallVec[i]->setHasHitEnemy();
                monstersVec[j]->looseLifePoints(cannonBallVec[i]->getAttackPower());
                break;
            }
        }
    }
}

void Environment::handleKeyPress(XEvent &event){
    KeySym key;
    char text[BufferSize];
    
    int i = XLookupString(
        (XKeyEvent *)&event,    // the keyboard event
        text,                   // buffer when text will be written
        BufferSize,             // size of the text buffer
        &key,                   // workstation-independent key symbol
        NULL );                 // pointer to a composeStatus structure (unused)
    if ( i == 1 ) {
        if (text[0] == 'q') {
            gameEnds();
            error("Terminating normally.");
        }
    }

    if (key == XK_Left) {
        cannon->setMoveBackward(true);
    } else if (key == XK_Right) {
        cannon->setMoveForward(true);
    }
}

void Environment::handleKeyRelease(XEvent &event){
    KeySym key;
    char text[BufferSize];
    
    int i = XLookupString(
        (XKeyEvent *)&event,    // the keyboard event
        text,                   // buffer when text will be written
        BufferSize,             // size of the text buffer
        &key,                   // workstation-independent key symbol
        NULL );                 // pointer to a composeStatus structure (unused)
    
    if ( i == 1 ) {
        if (text[0] == 'u') {
            increaseDifficulity();
        } else if (text[0] == 'b') {
            killAllMonsters();
        }
    }

    if (key == XK_Left) {
        cannon->setMoveBackward(false);
    } else if (key == XK_Right) {
        cannon->setMoveForward(false);
    } else if (key == XK_space) {
        cannon->fire();
    }
}

void Environment::handleKeyReleaseBeforeAfterGame(XEvent &event, bool &proceed){
    KeySym key;
    char text[BufferSize];
    
    int i = XLookupString(
        (XKeyEvent *)&event,    // the keyboard event
        text,                   // buffer when text will be written
        BufferSize,             // size of the text buffer
        &key,                   // workstation-independent key symbol
        NULL );                 // pointer to a composeStatus structure (unused)
    
    if (i == 1) {
        if (text[0] == 'q') {
            gameEnds();
            error("Quite the game!");
        }
    }

    if (key == XK_Return) {
        proceed = true;
    }
}

void Environment::handleAnimation() {
    //Check Collision.
    checkObjectCollision();

    //Cannon's action.
    cannon->move();
    cannon->updateOrRemoveCannonBalls(xInfo);

    // Remove dead monsters
    removeMonsters();

    // Move monsters.
    for (int i = 0; i < monstersVec.size(); ++i) {
        monstersVec[i]->move(castel);
    }

    // Spawn monsters.
    addMonster();
}

void Environment::handleResize(XEvent &event) {
    XConfigureEvent xce = event.xconfigure;
    if (xce.width > xInfo.width || xce.height > xInfo.height) {
        XFreePixmap(xInfo.display, xInfo.pixmap);
        int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
        xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, xce.width,
                                     xce.height, depth);
        xInfo.width = xce.width;
        xInfo.height = xce.height;
    }

}
