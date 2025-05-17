#include "Bullet.h"
#include <GL/glut.h>
#include <cmath>  // sin ve cos için


Bullet::Bullet() : x(0), y(0), dy(5.0f), active(false) {}

// user bullet (angle)
void Bullet::activateWithAngle(float startX, float startY, float angle) {
    float speed = 5.0f;
    dx = sin(angle) * speed;
    dy = cos(angle) * speed;
    x = startX;
    y = startY;
    useAngle = true;
    active = true;
}


// enemy bullet (only y direction)
void Bullet::activate(float startX, float startY, float dyVal) {
    x = startX;
    y = startY;
    dx = 0;
    dy = dyVal;
    useAngle = false;
    active = true;
}


void Bullet::deactivate() {
    active = false;
}

bool Bullet::isActive() const {
    return active;
}

float Bullet::getX() const {
    return x;
}

float Bullet::getY() const {
    return y;
}

//void Bullet::update() {
//    if (!active) return;
//    float speed = 5.0f;
//    x += sin(angle) * speed;
//    y += cos(angle) * speed;
//
//    if (y > 600 || x < 0 || x > 800) {
//        active = false;
//    }
//}

void Bullet::update() {
    if (!active) return;

    if (useAngle) {
        x += dx;
        y += dy;
    }
    else {
        y += dy;
    }

    if (y > 600 || y < 0 || x < 0 || x > 800) {
        active = false;
    }
}


void Bullet::draw() const {
    if (active) {
        // halo
        glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
        float radius = 8.0f;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int angle = 0; angle <= 360; angle += 20) {
            float rad = angle * 3.14159f / 180.0f;
            glVertex2f(x + std::cos(rad) * radius, y + std::sin(rad) * radius);
        }
        glEnd();

        // main
        if (useAngle) {
            glColor3f(1.0f, 1.0f, 0.5f);  
        }
        else {
            glColor3f(1.0f, 1.0f, 1.0f);  
        }
        //glColor3f(1.0f, 1.0f, 0.0f);  
        glBegin(GL_QUADS);
        glVertex2f(x - 2, y - 5);
        glVertex2f(x + 2, y - 5);
        glVertex2f(x + 2, y + 5);
        glVertex2f(x - 2, y + 5);
        glEnd();
    }
}


//void Bullet::draw() const {
//    if (active) {
//        glColor3f(1.0f, 1.0f, 0.0f);
//        glBegin(GL_QUADS);
//        glVertex2f(x - 2, y - 5);
//        glVertex2f(x + 2, y - 5);
//        glVertex2f(x + 2, y + 5);
//        glVertex2f(x - 2, y + 5);
//        glEnd();
//    }
//}
