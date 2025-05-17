#include "BulletPool.h"

BulletPool::BulletPool(int initialSize) {
    bullets.resize(initialSize); // initial bullets
}


Bullet* BulletPool::getBullet() {
    for (auto& bullet : bullets) {
        if (!bullet.isActive()) {
            return &bullet;
        }
    }
    return nullptr;
}

std::vector<Bullet>& BulletPool::getBullets() { 
    return bullets;
}

void BulletPool::update() {
    for (auto& bullet : bullets) {
        if (bullet.isActive()) {
            bullet.update();
        }
    }
}

void BulletPool::draw() const {
    for (const auto& bullet : bullets) {
        if (bullet.isActive()) {
            bullet.draw();
        }
    }
}
