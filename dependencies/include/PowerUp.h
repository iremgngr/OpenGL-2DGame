// PowerUp.h
#pragma once
#include "Color.h"
#include <GL/glut.h>

enum class PowerUpType { UPGRADE, HEALTH, SHIELD };

class PowerUp {
private:
    float x, y;
    float speed;
    PowerUpType type;
    bool active;

public:
    PowerUp(PowerUpType type, float x, float y);

    void update();
    void draw() const;
    bool isActive() const;
    void deactivate();
    PowerUpType getType() const;
    float getX() const;
    float getY() const;
};
#pragma once
