#pragma once

class Bullet {
private:
    float x, y;
    float dx, dy;   // direction
    bool active;
    bool useAngle = false;  // True → (dx, dy), False → only dy

public:
    Bullet();
    /*void activate(float startX, float startY, float direction = 1.0f);*/
    void activateWithAngle(float x, float y, float angle);         // For gamer
    void activate(float x, float y, float dyVal);         // For enemy
    void deactivate();
    bool isActive() const;

    float getX() const;
    float getY() const;
    float angle;

    void update();
    void draw() const;
};




//class Bullet {
//private:
//    float x, y;
//    float dy;   // Yön (yukarı +5, aşağı -5)
//    bool active;
//
//public:
//    Bullet();
//    void activate(float startX, float startY, float direction = 1.0f);
//    void deactivate();
//    bool isActive() const;
//
//    float getX() const;
//    float getY() const;
//
//    void update();
//    void draw() const;
//};

