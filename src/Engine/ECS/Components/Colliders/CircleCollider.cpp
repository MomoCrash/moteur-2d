#include "pch.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Entity* entity, int radius) : Collider2D(entity)
{
    mColliderType = ColliderType::CIRCLE;
    mRadius = radius;
    mpShape = new sf::CircleShape(radius);
    mpShape->setFillColor(sf::Color::Green);
    
}
