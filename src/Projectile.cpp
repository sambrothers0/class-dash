#include "Projectile.hpp"
#include "gameDimensions.hpp"

Projectile::Projectile(std::shared_ptr<GameLogic> _gameLogic, Vector2 playerPosition, MoveDirection playerDirection)
    : gameLogic(_gameLogic), currentDirection(playerDirection) {
    active = true;
    currentPosition.setX(playerPosition.getX());
    currentPosition.setY(playerPosition.getY());

    startingPosition.setX(playerPosition.getX());
    startingPosition.setY(playerPosition.getY());

    // Detect collisions with walls
}

// move the projectile along the x axis
void Projectile::move(double ms) {
    /*
    if (currentPosition.getX() < (startingPosition.getX() + 100) || (currentPosition.getX() > (startingPosition.getX() - 100))) {
        double seconds = ms/1000;
        //double moveOffset = currentPosition.getX() + velocity.getX() * seconds;
        double moveOffset = velocity.getX() * seconds;
        currentPosition.setX(currentPosition.getX() + moveOffset);
    }
    */
   /*
   if (std::abs(currentPosition.getX() - startingPosition.getX()) > 100) {
        double seconds = ms/1000;
        //double moveOffset = currentPosition.getX() + velocity.getX() * seconds;
        double moveOffset = velocity.getX() * seconds;
        currentPosition.setX(currentPosition.getX() + moveOffset);
    }
    else {
        setActive(false);
    }
    */
    double seconds = ms/1000;
    double moveOffset = velocity.getX() * seconds;
    currentPosition.setX(currentPosition.getX() + moveOffset);

    if (std::abs(currentPosition.getX() - startingPosition.getX()) > 500) {
        active = false;
    }

    // Detect collisions with walls
    auto hitboxPos = hitbox + currentPosition;
    auto leftX = hitboxPos.getLeftX();
    auto rightX = hitboxPos.getRightX();
    auto topY = hitboxPos.getTopY();
    auto bottomY = hitboxPos.getBottomY();
    
    auto level = gameLogic->getLevel();

    for (auto x : {leftX, rightX}) {
        for (auto y : {topY, bottomY}) {
            auto worldTile = level->getWorldCollisionObject(Vector2(
                floor(x / TILE_SIZE),
                floor(y / TILE_SIZE)
            ));

            if (worldTile) {
                if (hitboxPos.overlaps(BoundingBox(
                    Vector2(worldTile->bounds.x, worldTile->bounds.y),
                    Vector2(worldTile->bounds.w, worldTile->bounds.h)
                ))) {
                    active = false;
                    return;
                }
            }
        }
    }

    // Check for collisions with enemies
    auto enemies = level->getEnemies();
    
    for (auto enemy : enemies) {
        auto enemyHitbox = enemy->getHitbox() + enemy->getPosition();

        if (hitboxPos.overlaps(enemyHitbox)) {
            active = false;
            enemy->decrementHealth();
            break;
        }
    }
}

void Projectile::setStartingPosition(MoveDirection direction) {
    double offset = 20;

    if (direction == MoveDirection::LEFT) {
        startingPosition.setX(startingPosition.getX() - offset);
        currentPosition.setX(startingPosition.getX());
    }
    else if (direction == MoveDirection::RIGHT) {
        startingPosition.setX(startingPosition.getX() + offset);
        currentPosition.setX(startingPosition.getX());
    }
}

void Projectile::setVelocity(double x, double y) {
    velocity.setX(x);
    velocity.setY(y);
}