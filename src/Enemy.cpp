#include "Enemy.h"

Enemy::Enemy(float x, float y, float size, const Color& color)
    : x(x), y(y), size(size), color(color), isHit(false), hitTimer(0), maxHitFrames(10) {}

void Enemy::hit() {
    isHit = true;
    hitTimer = maxHitFrames;
}



float Enemy::getLeft() const {
    return x - size / 2;
}

float Enemy::getRight() const {
    return x + size / 2;
}

float Enemy::getTop() const {
    return y + size / 2;
}

float Enemy::getBottom() const {
    return y - size / 2;
}
