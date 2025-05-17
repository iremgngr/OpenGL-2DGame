#pragma once
#include "Bullet.h"
#include <vector>

class BulletPool {
private:
    std::vector<Bullet> bullets;

public:
    BulletPool(int initialSize = 50);

    Bullet* getBullet();
    std::vector<Bullet>& getBullets(); 

    void update();
    void draw() const;
};

