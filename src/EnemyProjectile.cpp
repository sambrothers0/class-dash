#include "EnemyProjectile.hpp"
#include "gameDimensions.hpp"
#include "characters/Player.hpp"
#include "GameLogic.hpp"

//EnemyProjectile::EnemyProjectile() {

//}

EnemyProjectile::EnemyProjectile(std::shared_ptr<GameLogic> _gameLogic, Vector2 enemyPosition, MoveDirection enemyDirection) : Projectile(_gameLogic, enemyPosition, enemyDirection) {
    //destination = gameLogic->getPlayer()->getPosition();
    auto player = gameLogic->getPlayer();
    if (player) {
        destination = player->getPosition();
    } 
}

void EnemyProjectile::move(double ms) {
    double seconds = ms/1000;

    double dirX = destination.getX() - currentPosition.getX();
    double dirY = destination.getY() - currentPosition.getY();

    double length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length == 0) return;
    dirX /= length;
    dirY /= length;

    double speed = velocity.magnitude();
    double moveOffsetX = dirX * speed * seconds;
    double moveOffsetY = dirY * speed * seconds;


    //double moveOffset = velocity.getX() * seconds;
    currentPosition.setX(currentPosition.getX() + moveOffsetX);
    currentPosition.setY(currentPosition.getY() + moveOffsetY);

    enemyProjTraveledDist += speed * seconds;

    if (enemyProjTraveledDist >= 500) {
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
}