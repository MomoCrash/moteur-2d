#include "pch.h"
#include "AABBCollider.h"

AABBCollider::AABBCollider(Entity* entity, float xMin, float yMin, float xMax, float yMax) : Collider2D(entity)
{
    mColliderType = ColliderType::AABB;
    mXMax = xMax;
    mYMax = yMax;
    mXMin = xMin;
    mYMin = yMin;
    mpShape = new sf::RectangleShape(sf::Vector2f(mXMax, mYMax));
    mpShape->setFillColor(sf::Color::Green);
    
}
