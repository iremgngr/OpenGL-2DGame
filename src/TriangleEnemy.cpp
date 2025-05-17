#include "TriangleEnemy.h"
#include <GL/glut.h>
#include <cmath>

TriangleEnemy::TriangleEnemy(float x, float y, float size, const Color& color)
    : Enemy(x, y, size, color), fireCooldown(120), fireTimer(0) {  // ~2 saniyede bir ateþ eder
    bullets.resize(5);  // Her düþmanýn 5 mermilik stoðu var
}

void TriangleEnemy::update() {

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

    if (fireTimer <= 0) {

        for (auto& bullet : bullets) {
            if (!bullet.isActive()) {
                bullet.activate(x, y - size / 2, -4.0f);
                fireTimer = fireCooldown;         // Cooldown reset
                break;
            }
        }
    }
    else {
        --fireTimer;
    }

    // update enemy bullets
    for (auto& bullet : bullets) {
        bullet.update();
    }
}

void TriangleEnemy::draw() const {

    if (isHit) {
        glPushMatrix();
        glTranslatef(rand() % 5 - 2, rand() % 5 - 2, 0);
    }

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + size / 2);
    glVertex2f(x - size / 2, y - size / 2);
    glVertex2f(x + size / 2, y - size / 2);
    glEnd();

    if (isHit) {
        glPopMatrix();
    }

    for (const auto& bullet : bullets) {
        bullet.draw();
    }
}

bool TriangleEnemy::isDestroyed() const {
    return isHit && hitTimer <= 0;
}

std::vector<Bullet>& TriangleEnemy::getBullets() {
    return bullets;
}
