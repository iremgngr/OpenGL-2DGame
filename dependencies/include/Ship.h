#pragma once
#include "BulletPool.h"
#include "Color.h"

class Ship {
private:
    float x, y;
    float size;
    BulletPool* bulletPool;

public:
    Ship(float x, float y, float size, BulletPool* bulletPool);
    void update();
    void draw() const;
    void moveLeft();
    void moveRight();
    void shoot(bool upgradeActive = false);

    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;

};