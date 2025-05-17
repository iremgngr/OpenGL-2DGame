#pragma once
#include "Ship.h"
#include "Level.h"
#include "BulletPool.h"
#include "PowerUp.h"
#include <vector>


class Game {
private:
    Ship* ship;
    BulletPool bulletPool;
    Level level;
    std::vector<PowerUp> powerUps;

    bool shieldActive = false;
    int shieldTimer = 0;

    bool upgradeActive = false;
    int upgradeTimer = 0;


    bool isShooting;
    int fireCooldown;
    int fireTimer;
    int playerHealth;
    bool gameOver;

public:
    Game();
    void init();
    void update();
    void render();
    void handleKeyPress(int key);
    void handleMouse(int button, int state);
    void onTimer();
};
