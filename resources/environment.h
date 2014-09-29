/*
 * Environment header file.
 */
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include "monster.h"
#include "castel.h"
#include "cannon.h"
#include "window.h"

using namespace std;

class Environment {
    public:
        // Initialize environment.
        Environment(XInfo &xInfo);
        void initCastel();
        void initMonster();
        void initCannon();

        // Environment functions.
        XInfo &getXInfo();
        void paint();
        void paintGuideline();
        void paintGameOver();
        void gameEnds();
        bool hasGameEnded();
        void addMonster();
        void removeMonsters();
        bool isMouseInside();
        void addMoney(int gold);
        void checkObjectCollision();
        void setMonsterSpawnTimer(int level);
        void increaseDifficulity();
        void killAllMonsters();

        // Handle global events.
        void handleKeyPress(XEvent &event);
        void handleKeyRelease(XEvent &event);
        void handleKeyReleaseBeforeAfterGame(XEvent &event, bool &proceed);
        void handleAnimation();
        void handleResize(XEvent &event);
        void setIsMouseInside(bool value);

    private:
        int difficulty;
        int lastSpawnTime;
        int spawnTimer;
        int money;
        bool isInsideScreen;
        XInfo &xInfo;
        vector<Monster *> monstersVec;
        Castel *castel;
        Cannon *cannon;
};

#endif
