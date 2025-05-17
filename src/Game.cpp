#include "Game.h"
#include <GL/glut.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <iostream>
#include <cmath>

Game::Game()
    : ship(nullptr), bulletPool(50), level(), isShooting(false), fireCooldown(15), fireTimer(0),
    playerHealth(3), gameOver(false)
{}

void drawPixelHeart(float x, float y, float s) {
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);

    // Top left piece
    glVertex2f(x + s * 1, y + s * 3);
    glVertex2f(x + s * 2, y + s * 3);
    glVertex2f(x + s * 2, y + s * 4);
    glVertex2f(x + s * 1, y + s * 4);

    // Top right piece
    glVertex2f(x + s * 3, y + s * 3);
    glVertex2f(x + s * 4, y + s * 3);
    glVertex2f(x + s * 4, y + s * 4);
    glVertex2f(x + s * 3, y + s * 4);

    // Middle block
    glVertex2f(x + s * 0, y + s * 2);
    glVertex2f(x + s * 5, y + s * 2);
    glVertex2f(x + s * 5, y + s * 3);
    glVertex2f(x + s * 0, y + s * 3);

    // Bottom wide block
    glVertex2f(x + s * 1, y + s * 1);
    glVertex2f(x + s * 4, y + s * 1);
    glVertex2f(x + s * 4, y + s * 2);
    glVertex2f(x + s * 1, y + s * 2);

    // Tip part
    glVertex2f(x + s * 2, y + s * 0);
    glVertex2f(x + s * 3, y + s * 0);
    glVertex2f(x + s * 3, y + s * 1);
    glVertex2f(x + s * 2, y + s * 1);

    glEnd();
}

void Game::init() {
    ship = new Ship(400.0f, 50.0f, 40.0f, &bulletPool);  // Centered ship
    upgradeActive = true;
    upgradeTimer = 600;

    std::cout << "[DEBUG] Upgrade power-up FORCE STARTED (for testing)\n";

    playerHealth = 1;  // Simulate missing health
    PowerUpType type = PowerUpType::HEALTH;
    powerUps.emplace_back(type, 400.0f, 300.0f);  // drop in center

    std::cout << "Player health: " << playerHealth << std::endl;

    shieldActive = true;
    shieldTimer = 600;
    std::cout << "Shield activated manually!\n";
}

void Game::update() {

    if (gameOver) {
        return;
    }

    if (ship) {
        ship->update();
    }

    level.update();
    bulletPool.update();

    // Bullet-enemy collision check
    for (auto& enemy : level.getEnemies()) {
        for (auto& bullet : bulletPool.getBullets()) {
            if (bullet.isActive()) {
                if (bullet.getX() > enemy->getLeft() &&
                    bullet.getX() < enemy->getRight() &&
                    bullet.getY() > enemy->getBottom() &&
                    bullet.getY() < enemy->getTop()) {

                    enemy->hit();

                    // Power-up generation (limited and random)
                    if (rand() % 10 == 0 && powerUps.size() < 3) {
                        PowerUpType type;
                        int r = rand() % 100;

                        if (r < 40)
                            type = PowerUpType::UPGRADE;
                        else if (r < 70)
                            type = PowerUpType::HEALTH;
                        else
                            type = PowerUpType::SHIELD;

                        powerUps.emplace_back(type, enemy->getX(), enemy->getY());
                    }

                    bullet.deactivate();
                }
            }
        }
    }

    // Check if enemy bullets hit the player
    for (auto& enemy : level.getEnemies()) {
        TriangleEnemy* triangle = dynamic_cast<TriangleEnemy*>(enemy.get());
        if (triangle) {
            for (auto& bullet : triangle->getBullets()) {
                if (bullet.isActive()) {
                    if (bullet.getX() > ship->getLeft() &&
                        bullet.getX() < ship->getRight() &&
                        bullet.getY() > ship->getBottom() &&
                        bullet.getY() < ship->getTop()) {

                        bullet.deactivate();

                        if (!shieldActive) {
                            playerHealth--;
                        }

                        if (playerHealth <= 0) {
                            gameOver = true;
                        }
                    }
                }
            }
        }
    }

    // Shooting logic
    if (isShooting && fireTimer <= 0) {
        ship->shoot(upgradeActive);
        fireTimer = fireCooldown;
    }

    if (fireTimer > 0) {
        --fireTimer;
    }

    if (upgradeActive && --upgradeTimer <= 0) {
        upgradeActive = false;
    }

    if (shieldActive && --shieldTimer <= 0) {
        shieldActive = false;
    }

    // Update power-ups
    for (auto& powerUp : powerUps) {
        powerUp.update();
    }

    // Remove inactive power-ups
    powerUps.erase(std::remove_if(powerUps.begin(), powerUps.end(),
        [](PowerUp& p) { return !p.isActive(); }),
        powerUps.end());

    // Check if player collects any power-up
    for (auto& powerUp : powerUps) {
        if (ship && powerUp.isActive()) {
            float shipX = (ship->getLeft() + ship->getRight()) / 2.0f;
            float shipY = (ship->getTop() + ship->getBottom()) / 2.0f;

            if (abs(powerUp.getX() - shipX) < 20 &&
                abs(powerUp.getY() - shipY) < 20) {

                switch (powerUp.getType()) {
                case PowerUpType::UPGRADE:
                    upgradeActive = true;
                    upgradeTimer = 600;
                    break;
                case PowerUpType::HEALTH:
                    playerHealth = std::min(playerHealth + 1, 3);
                    std::cout << "Health picked up! New health: " << playerHealth << std::endl;
                    break;
                case PowerUpType::SHIELD:
                    shieldActive = true;
                    shieldTimer = 600;
                    break;
                }

                powerUp.deactivate();
            }
        }
    }

    // Remove destroyed enemies
    auto& enemies = level.getEnemies();
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& e) {
                return e->isDestroyed();
            }),
        enemies.end());

    // Respawn if all enemies are gone
    if (level.getEnemies().empty()) {
        level.spawnEnemies();
    }
}

void Game::render() {
    if (ship) {
        ship->draw();

        // Halo effect if upgrade is active
        if (upgradeActive) {
            float shipX = (ship->getLeft() + ship->getRight()) / 2.0f;
            float shipY = (ship->getTop() + ship->getBottom()) / 2.0f;

            glColor4f(1.0f, 1.0f, 0.0f, 0.3f);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(shipX, shipY);
            for (int angle = 0; angle <= 360; angle += 10) {
                float rad = angle * 3.14159f / 180;
                glVertex2f(shipX + cos(rad) * 40, shipY + sin(rad) * 40);
            }
            glEnd();
        }

        // Shield effect if active
        if (shieldActive) {
            float shipX = (ship->getLeft() + ship->getRight()) / 2.0f;
            float shipY = (ship->getTop() + ship->getBottom()) / 2.0f;

            glColor4f(0.0f, 0.5f, 1.0f, 0.3f);
            glBegin(GL_TRIANGLE_FAN);
            glVertex2f(shipX, shipY);
            for (int angle = 0; angle <= 360; angle += 10) {
                float rad = angle * 3.14159f / 180;
                glVertex2f(shipX + cos(rad) * 50, shipY + sin(rad) * 50);
            }
            glEnd();
        }
    }

    level.draw();
    bulletPool.draw();

    // Draw player health (top-left corner)
    for (int i = 0; i < playerHealth; ++i) {
        float x = 10.0f + i * 30.0f;
        float y = 570.0f;
        drawPixelHeart(x, y, 5.0f);
    }

    if (gameOver) {
        // Game Over text
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(350.0f, 300.0f);
        const char* text = "GAME OVER";
        for (const char* c = text; *c != '\0'; ++c) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        }
    }

    // Draw power-ups
    for (const auto& powerUp : powerUps) {
        powerUp.draw();
    }

    // Upgrade timer (HUD)
    if (upgradeActive) {
        glColor3f(1.0f, 1.0f, 0.0f);
        glRasterPos2f(650, 570);
        std::string text = "Upgrade: " + std::to_string(upgradeTimer / 60) + "s";
        for (char c : text) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
        }
    }

    // Shield timer (HUD)
    if (shieldActive) {
        glColor3f(0.5f, 0.8f, 1.0f);
        glRasterPos2f(650, 550);
        std::string text = "Shield: " + std::to_string(shieldTimer / 60) + "s";
        for (char c : text) {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
        }
    }
}

void Game::handleKeyPress(int key) {
    if (key == GLUT_KEY_LEFT) {
        ship->moveLeft();
    }
    else if (key == GLUT_KEY_RIGHT) {
        ship->moveRight();
    }
    else if (key == ' ') {  // Spacebar for shooting
        isShooting = true;
    }

    else if (gameOver && key == 'r') {  // Restart game
        playerHealth = 3;
        gameOver = false;
        level.spawnEnemies();
    }
}

void Game::handleMouse(int button, int state) {
    if (button == GLUT_LEFT_BUTTON) {
        isShooting = (state == GLUT_DOWN);
    }
}

void Game::onTimer() {
    update();
    glutPostRedisplay();  // Redraw screen
}
