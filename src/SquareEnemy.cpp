#include "SquareEnemy.h"
#include <GL/glut.h>

#include "SquareEnemy.h"

SquareEnemy::SquareEnemy(float x, float y, float size, const Color& color)
    : Enemy(x, y, size, color) {}

void SquareEnemy::update() {

    if (powerUpCooldown > 0) {
        --powerUpCooldown;
        if (powerUpCooldown == 0) {
            justDroppedPowerUp = false;
        }
    }

    if (isHit) {
        hitTimer--;
        if (hitTimer <= 0) {
            isHit = false;
        }
    }
}


void SquareEnemy::draw() const {
    if (isHit) {
        float scale = static_cast<float>(hitTimer) / maxHitFrames;
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_QUADS);
        glVertex2f(x - size / 2 * scale, y - size / 2 * scale);
        glVertex2f(x + size / 2 * scale, y - size / 2 * scale);
        glVertex2f(x + size / 2 * scale, y + size / 2 * scale);
        glVertex2f(x - size / 2 * scale, y + size / 2 * scale);
        glEnd();
    }
    else {
        // Normal hali
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_QUADS);
        glVertex2f(x - size / 2, y - size / 2);
        glVertex2f(x + size / 2, y - size / 2);
        glVertex2f(x + size / 2, y + size / 2);
        glVertex2f(x - size / 2, y + size / 2);
        glEnd();
    }
}


//void SquareEnemy::draw() const {
//    glColor3f(color.r, color.g, color.b);
//    glBegin(GL_QUADS);
//    glVertex2f(x - size / 2, y - size / 2);
//    glVertex2f(x + size / 2, y - size / 2);
//    glVertex2f(x + size / 2, y + size / 2);
//    glVertex2f(x - size / 2, y + size / 2);
//    glEnd();
//}

bool SquareEnemy::isDestroyed() const {  
    return y + size / 2 < 0;
}
