#pragma once
#include "Color.h"


class Enemy {
protected:
    float x, y;
    float size;
    Color color;

    bool isHit;
    int hitTimer;
    const int maxHitFrames;

public:
    Enemy(float x, float y, float size, const Color& color);
    virtual ~Enemy() = default;

    virtual void update() = 0;
    virtual void draw() const = 0;

    void hit();
    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;
    int powerUpCooldown = 0;     
    bool justDroppedPowerUp = false;


    /*virtual bool isDestroyed() const = 0;*/
    virtual bool isDestroyed() const {
        return isHit && hitTimer <= 0; 
    }

    float getX() const { return x; }
    void setX(float newX) { x = newX; }

    float getY() const { return y; }
    void setY(float newY) { y = newY; }
};



//class Enemy {
//protected:
//    float x, y;
//    float size;
//    Color color;
//    bool isHit;
//    int hitTimer;
//    int maxHitFrames;
//
//public:
//    Enemy(float x, float y, float size, const Color& color);
//    virtual ~Enemy() = default;
//
//    virtual void update() = 0;
//    virtual void draw() const = 0;
//    virtual bool isDestroyed() const = 0;
//
//    virtual void hit();
//
//    float getLeft() const;
//    float getRight() const;
//    float getTop() const;
//    float getBottom() const;
//};
