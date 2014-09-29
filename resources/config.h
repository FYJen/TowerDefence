#ifndef CONFIG_H
#define CONFIG_H

// World variables.
const int Border = 5;
const int BufferSize = 64;
const int FPS = 30;
const float GRAVITY = 9.81;
const float INITIAL_GOLD = 20;
const float MAX_DIFFICULITY = 3;

// Monster.
const int MONSTER_LIFE_POINTS = 6;
const int ATTACK_POWER = 10;
const int MONSTER_MOVE_SPEED = 3;
const int MONSTER_SPAWN_TIME_LVL1 = 10;
const int MONSTER_SPAWN_TIME_LVL2 = 5;
const int MONSTER_SPAWN_TIME_LVL3 = 1;
const int MONSTER_AWARD_GOLD = 5;

// Castel.
const int CASTEL_LIFE_POINTS = 100;
const int CASTEL_LEVEL = 1;
const int MAX_CASTEL_LEVEL = 5;

// Cannon.
const int CANNON_MOVE_SPEED = 5;

// Cannon Ball.
const int CANNON_BALL_INIT_VELOCITY = 1;
const int CANNON_BALL_ATTACK_POWER = 1;

// Objects Ratio.
const int SCREEN_TO_CASTEL= 3;
const int SCREEN_TO_MONSTER = 15;
const int SCREEN_TO_CANNON = 15;

#endif
