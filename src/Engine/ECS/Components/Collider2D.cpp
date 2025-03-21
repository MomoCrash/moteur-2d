#include "pch.h"
#include "Collider2D.h"

#include "ObjectFactory.h"
#include "Colliders/AABBCollider.h"
#include "Colliders/CircleCollider.h"
#include "PhysicsMaterial.h"

Collider2D::Collider2D(Entity* entity) : Component(entity)
{
    mColliderType = ColliderType::COLLIDER_COUNT;

    mCenter = entity->GetTransform()->position;
    mIsTrigger = false;
    mIsStatic = false;
    SetCenter(entity->GetTransform()->position);

    ObjectFactory::CreateComponent<PhysicsMaterial>(entity);
}

int Collider2D::GetBitmask()
{
    return BITMASK;
}

CollisionManifold Collider2D::Intersects(Collider2D* Collider)
{
    CollisionManifold manifold;
    ColliderType entity1 = this->GetColliderType();
    ColliderType entity2 = Collider->GetColliderType();

    switch(entity1)
    {
    case ColliderType::CIRCLE:
        if (entity2 == ColliderType::CIRCLE) return CheckCollisionCircleCircle(Collider);
        if (entity2 == ColliderType::AABB) return CheckCollisionCircleBox(Collider);
        break;

    case ColliderType::AABB:
        if (entity2 == ColliderType::CIRCLE) return CheckCollisionCircleBox(Collider);
        if (entity2 == ColliderType::AABB) return CheckCollisionBoxBox(Collider);
        break;
    }

    return manifold;
}

CollisionManifold Collider2D::CheckCollisionCircleCircle(Collider2D* Collider)
{
    CollisionManifold manifold;
    CircleCollider* CCollider1 = static_cast<CircleCollider*>(this);
    CircleCollider* CCollider2 = static_cast<CircleCollider*>(Collider);
    
    float a = CCollider1->mCenter.x - CCollider2->mCenter.x;
    float b = CCollider1->mCenter.y - CCollider2->mCenter.y;
    float c = (a * a) + (b * b); 
    float radiusSum = CCollider1->GetRadius() + CCollider2->GetRadius();

    if (c <= radiusSum * radiusSum)
    {  
        manifold.hasCollision = true;

        manifold.collisionNormal = (CCollider1->mCenter - CCollider2->mCenter).normalized();
        manifold.penetrationDepth = radiusSum - std::sqrt(c);
    }

    return manifold;
}


CollisionManifold Collider2D::CheckCollisionBoxBox(Collider2D* BoxCollider)
{
    AABBCollider* AABBCollider1 = static_cast<AABBCollider*>(this);
    AABBCollider* AABBCollider2 = static_cast<AABBCollider*>(BoxCollider);

    sf::Vector2f b1Pos = GetEntity()->GetTransform()->position;
    sf::Vector2f b2Pos = BoxCollider->GetEntity()->GetTransform()->position;
    
    float minX1 = AABBCollider1->GetMinX() + b1Pos.x;
    float maxX1 = AABBCollider1->GetMaxX() + b1Pos.x;
    float minY1 = AABBCollider1->GetMinY() + b1Pos.y;
    float maxY1 = AABBCollider1->GetMaxY() + b1Pos.y;
    
    float minX2 = AABBCollider2->GetMinX() + b2Pos.x;
    float maxX2 = AABBCollider2->GetMaxX() + b2Pos.x;
    float minY2 = AABBCollider2->GetMinY() + b2Pos.y;
    float maxY2 = AABBCollider2->GetMaxY() + b2Pos.y;
    
    CollisionManifold manifold;

    if (maxX1 <= minX2 || maxX2 <= minX1)
    {
        manifold.hasCollision = false;
        return manifold;
    }

    if (maxY1 <= minY2 || maxY2 <= minY1)
    {
        manifold.hasCollision = false;
        return manifold;
    }

    float overlapX = std::min(maxX1 - minX2, maxX2 - minX1);
    float overlapY = std::min(maxY1 - minY2, maxY2 - minY1);

    if (overlapX < overlapY)
    {
        if (minX2 < minX1 && maxX2 > minX1)
        {
            manifold.collisionNormal = sf::Vector2f(1, 0); 
        }
        else
        {
            manifold.collisionNormal = sf::Vector2f(-1, 0); 
        }
        manifold.penetrationDepth = overlapX;
    }
    else
    {
        if (minY2 < minY1 && maxY2 > minY1)
        {
            manifold.collisionNormal = sf::Vector2f(0, 1); 
        }
        else
        {
            manifold.collisionNormal = sf::Vector2f(0, -1); 
        }
        manifold.penetrationDepth = overlapY;
    }

    manifold.hasCollision = true;
    
    return manifold;
}


sf::Vector2f Clamp(sf::Vector2f& value, sf::Vector2f minValue, sf::Vector2f maxValue)     
{
    value.x = std::clamp(value.x, minValue.x, maxValue.x);
    value.y = std::clamp(value.y, minValue.y, maxValue.y);
    
    return value;
}

float ClosestPtPointBoxCollider(const sf::Vector2f& p, const AABBCollider* b, sf::Vector2f& q)
{
    sf::Vector2f boxPosition = b->GetEntity()->GetTransform()->position;

    sf::Vector2f worldMin = sf::Vector2f(b->GetMinX(), b->GetMinY()) + boxPosition;
    sf::Vector2f worldMax = sf::Vector2f(b->GetMaxX(), b->GetMaxY()) + boxPosition;

    sf::Vector2f point = p;

    sf::Vector2f closestPoint = Clamp(point, worldMin, worldMax);

    q = closestPoint;

    sf::Vector2f diff = point - closestPoint;
    float sqDist = diff.lengthSquared();

    return sqDist;
}

CollisionManifold Collider2D::CheckCollisionCircleBox(Collider2D* Collider2)
{
    CircleCollider* circle;
    AABBCollider* box;

    if(this->mColliderType == ColliderType::CIRCLE)
    {
        circle = static_cast<CircleCollider*>(this);
        box = static_cast<AABBCollider*>(Collider2);
    }
    else
    {
        circle = static_cast<CircleCollider*>(Collider2);
        box = static_cast<AABBCollider*>(this);
    }

    sf::FloatRect boxBounds = box->GetShape()->getGlobalBounds();
    sf::FloatRect circleBounds = circle->GetShape()->getGlobalBounds();

    if (boxBounds.findIntersection(circleBounds))
    {
        sf::Vector2f b1Pos = boxBounds.position;
        sf::Vector2f b2Pos = circleBounds.position;
    
        float minX1 = boxBounds.position.x;
        float maxX1 = boxBounds.size.x + b1Pos.x;
        float minY1 = boxBounds.position.y;
        float maxY1 = boxBounds.size.y + b1Pos.y;
    
        float minX2 = circleBounds.position.x;
        float maxX2 = circleBounds.size.x + b2Pos.x;
        float minY2 = circleBounds.position.y;
        float maxY2 = circleBounds.size.y + b2Pos.y;
    
        CollisionManifold manifold;

        if (maxX1 <= minX2 || maxX2 <= minX1)
        {
            manifold.hasCollision = false;
            return manifold;
        }

        if (maxY1 <= minY2 || maxY2 <= minY1)
        {
            manifold.hasCollision = false;
            return manifold;
        }

        float overlapX = std::min(maxX1 - minX2, maxX2 - minX1);
        float overlapY = std::min(maxY1 - minY2, maxY2 - minY1);

        if (overlapX < overlapY)
        {
            if (minX2 < minX1 && maxX2 > minX1)
            {
                manifold.collisionNormal = sf::Vector2f(1, 0); 
            }
            else
            {
                manifold.collisionNormal = sf::Vector2f(-1, 0); 
            }
            manifold.penetrationDepth = overlapX;
        }
        else
        {
            if (minY2 < minY1 && maxY2 > minY1)
            {
                manifold.collisionNormal = sf::Vector2f(0, 1); 
            }
            else
            {
                manifold.collisionNormal = sf::Vector2f(0, -1); 
            }
            manifold.penetrationDepth = overlapY;
        }

        manifold.hasCollision = true;
    
        return manifold;
    }

}

