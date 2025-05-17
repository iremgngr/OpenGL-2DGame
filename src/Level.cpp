#include "Level.h"
#include <cstdlib>  
#include <ctime>   
#include <algorithm>

Level::Level()
    : enemySpeed(1.0f), moveDirection(1.0f), leftBoundary(50.0f), rightBoundary(750.0f),
    respawnCooldown(0) { 
    spawnEnemies();
}


void Level::spawnEnemies() {
    enemies.clear();

    int rows = 2;
    int cols = 10;

    float spacingX = 60.0f;       
    float spacingY = 60.0f;      
    float startX = 100.0f;       
    float startY = 480.0f;       

    leftBoundary = 50.0f;
    rightBoundary = 750.0f;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startX + col * spacingX;
            float y = startY - row * spacingY;
            float size = 30.0f;

            Color color(1.0f, 0.0f, 0.0f);  
            enemies.push_back(std::make_unique<SquareEnemy>(x, y, size, color));
        }
    }

    // Triangle enemies
    float triangleY = 540.0f;               
    float size = 30.0f;
    Color triangleColor(0.0f, 0.0f, 1.0f);  

    enemies.push_back(std::make_unique<TriangleEnemy>(280.0f, triangleY, size, triangleColor)); 
    enemies.push_back(std::make_unique<TriangleEnemy>(400.0f, triangleY, size, triangleColor));  
    enemies.push_back(std::make_unique<TriangleEnemy>(520.0f, triangleY, size, triangleColor));  
}



void Level::update() {
    bool changeDirection = false;

    for (auto& enemy : enemies) {
        enemy->setX(enemy->getX() + moveDirection * enemySpeed);

        if (enemy->getLeft() <= leftBoundary || enemy->getRight() >= rightBoundary) {
            changeDirection = true;
        }

        enemy->update();
    }

    if (changeDirection) {
        moveDirection *= -1.0f;
    }

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](const std::unique_ptr<Enemy>& enemy) { return enemy->isDestroyed(); }),
        enemies.end()
    );

    if (enemies.size() < 20) {
        if (respawnCooldown <= 0) {
            float x = static_cast<float>(std::rand() % 600 + 100);
            float y = static_cast<float>(std::rand() % 100 + 450);
            float size = 30.0f;

            Color color(1.0f, 0.0f, 0.0f);
            enemies.push_back(std::make_unique<SquareEnemy>(x, y, size, color));

            respawnCooldown = 50;
        }
        else {
            --respawnCooldown;
        }
    }

}


void Level::draw() const {
    for (const auto& enemy : enemies) {
        enemy->draw();
    }
}

std::vector<std::unique_ptr<Enemy>>& Level::getEnemies() {
    return enemies;
}
