// PowerUp.cpp
#include "PowerUp.h"

//PowerUp::PowerUp(PowerUpType t, float xPos, float yPos)
//    : type(t), x(xPos), y(yPos), speed(2.0f), active(true) {}

PowerUp::PowerUp(PowerUpType type, float x, float y)
    : type(type), x(x), y(y), active(true)
{
    speed = 1.0f + (rand() % 20) / 10.0f;
}



void PowerUp::update() {
    y -= speed;
    if (y < -20) active = false;
}

void PowerUp::draw() const {
    if (!active) return;
    switch (type) {
    case PowerUpType::UPGRADE: glColor3f(1.0f, 1.0f, 0.0f); break;
    case PowerUpType::HEALTH:  glColor3f(0.0f, 1.0f, 0.0f); break;
    case PowerUpType::SHIELD:  glColor3f(0.0f, 1.0f, 1.0f); break;
    }
    glBegin(GL_QUADS);
    glVertex2f(x - 10, y - 10); glVertex2f(x + 10, y - 10);
    glVertex2f(x + 10, y + 10); glVertex2f(x - 10, y + 10);
    glEnd();
}

bool PowerUp::isActive() const { return active; }
void PowerUp::deactivate() { active = false; }
PowerUpType PowerUp::getType() const { return type; }
float PowerUp::getX() const { return x; }
float PowerUp::getY() const { return y; }
