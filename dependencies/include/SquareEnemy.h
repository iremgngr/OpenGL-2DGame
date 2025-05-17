#pragma once
#include "Enemy.h"

class SquareEnemy : public Enemy {
public:
    SquareEnemy(float x, float y, float size, const Color& color);
    void update() override;
    void draw() const override;
    bool isDestroyed() const override;
};
