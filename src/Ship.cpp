#include "Ship.h"
#include <GL/glut.h>

Ship::Ship(float x, float y, float size, BulletPool* bulletPool)
    : x(x), y(y), size(size), bulletPool(bulletPool) {}

void Ship::update() {
}

//void Ship::draw() const {
//    glColor3f(0.0f, 0.0f, 1.0f);  // Mavi gemi
//    glBegin(GL_TRIANGLES);
//    glVertex2f(x, y + size / 2);
//    glVertex2f(x - size / 2, y - size / 2);
//    glVertex2f(x + size / 2, y - size / 2);
//    glEnd();
//}

//void Ship::draw() const {
//    glColor3f(0.0f, 0.5f, 1.0f);  // mavi
//
//    // Alt yarım daire
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(x, y);
//    for (int angle = 0; angle <= 180; angle += 10) {
//        float rad = angle * 3.14159f / 180.0f;
//        glVertex2f(x + cos(rad) * size, y + sin(rad) * size / 1.5f);
//    }
//    glEnd();
//
//    // Üst gözetleme kısmı
//    glColor3f(0.3f, 0.8f, 1.0f);
//    glBegin(GL_QUADS);
//    glVertex2f(x - size / 4, y + size / 3);
//    glVertex2f(x + size / 4, y + size / 3);
//    glVertex2f(x + size / 4, y + size / 1.2f);
//    glVertex2f(x - size / 4, y + size / 1.2f);
//    glEnd();
//}

void Ship::draw() const {
    float s = 3.0f; 
    float offsetX = x - 7 * s; 
    float offsetY = y;

    auto drawBlock = [&](int px, int py, float r, float g, float b) {
        glColor3f(r, g, b);
        float bx = offsetX + px * s;
        float by = offsetY + py * s;
        glBegin(GL_QUADS);
        glVertex2f(bx,     by);
        glVertex2f(bx + s, by);
        glVertex2f(bx + s, by + s);
        glVertex2f(bx,     by + s);
        glEnd();
    };


    // Mavi kokpit
    drawBlock(6, 11, 0.3f, 0.6f, 1.0f);
    drawBlock(6, 10, 0.2f, 0.5f, 1.0f);
    drawBlock(6, 9,  0.1f, 0.3f, 0.6f);

    // Üst gri gövde
    drawBlock(5, 12, 0.7f, 0.7f, 0.7f);
    drawBlock(6, 12, 0.7f, 0.7f, 0.7f);
    drawBlock(7, 12, 0.7f, 0.7f, 0.7f);

    // Orta siyah gövde
    for (int i = 8; i <= 11; ++i) {
        drawBlock(5, i, 0.3f, 0.3f, 0.3f);
        drawBlock(7, i, 0.3f, 0.3f, 0.3f);
    }

    // Alt gövde
    drawBlock(6, 7, 0.6f, 0.6f, 0.6f);

    // Yan kanatlar (simetrik)
    drawBlock(3, 9, 0.5f, 0.5f, 0.5f);
    drawBlock(9, 9, 0.5f, 0.5f, 0.5f);
    drawBlock(2, 8, 0.4f, 0.4f, 0.4f);
    drawBlock(10,8, 0.4f, 0.4f, 0.4f);

    // Silahlar (açık gri)
    drawBlock(1, 7, 0.6f, 0.6f, 0.6f);
    drawBlock(11,7, 0.6f, 0.6f, 0.6f);

    // Silah ucu (kırmızı)
    drawBlock(1, 6, 1.0f, 0.2f, 0.0f);
    drawBlock(11,6, 1.0f, 0.2f, 0.0f);
}



void Ship::moveLeft() {
    x -= 10.0f;
}

void Ship::moveRight() {
    x += 10.0f;
}

//void Ship::shoot() {
//    Bullet* bulletLeft = bulletPool->getBullet();
//    if (bulletLeft) {
//        bulletLeft->activate(x - size / 4, y + size / 2);
//    }
//
//    Bullet* bulletRight = bulletPool->getBullet();
//    if (bulletRight) {
//        bulletRight->activate(x + size / 4, y + size / 2);
//    }
//}

void Ship::shoot(bool upgradeActive) {
    if (upgradeActive) {
        float angles[] = { -0.2f, 0.0f, 0.2f };
        for (float angle : angles) {
            Bullet* bullet = bulletPool->getBullet();
            if (bullet) {
                bullet->activateWithAngle(x, y + size / 2, angle); 
            }
        }
    }
    else {
        Bullet* bulletLeft = bulletPool->getBullet();
        if (bulletLeft) {
            bulletLeft->activateWithAngle(x - size / 4, y + size / 2, 0.0f); 
        }

        Bullet* bulletRight = bulletPool->getBullet();
        if (bulletRight) {
            bulletRight->activateWithAngle(x + size / 4, y + size / 2, 0.0f); 
        }
    }
}




float Ship::getLeft() const {
    return x - size / 2;
}

float Ship::getRight() const {
    return x + size / 2;
}

float Ship::getTop() const {
    return y + size / 2;
}

float Ship::getBottom() const {
    return y - size / 2;
}


