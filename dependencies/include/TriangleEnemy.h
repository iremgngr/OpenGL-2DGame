#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class TriangleEnemy : public Enemy {
private:
    std::vector<Bullet> bullets;  
    int fireCooldown;            
    int fireTimer;

public:
    TriangleEnemy(float x, float y, float size, const Color& color);

    void update() override;
    void draw() const override;
    bool isDestroyed() const override;

    std::vector<Bullet>& getBullets();
};

