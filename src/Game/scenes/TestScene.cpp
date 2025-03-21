#include "pch.h"
#include "TestScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Colliders/CircleCollider.h"

#include "scripts/PlayerMovement.h"
void TestScene::OnEnter()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Resources::instance().Initialize();
    
    player = ObjectFactory::CreateEntity<Entity>(1);
    player->GetTransform()->SetPosition(0.0f, 0.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    //ObjectFactory::CreateComponent<AABBCollider>(player, 0.0f,0.0f,10.0f,10.0f);
    ObjectFactory::CreateComponent<CircleCollider>(player, 10.0f);
    player->SetTag(Entity::Tag::PLAYER);
    
    ObjectFactory::AttachScript<PlayerMovement>(player);

    
    Entity* other = ObjectFactory::CreateEntity<Entity>(0);
    other->GetTransform()->SetPosition(250.0f,250.0f);
    ObjectFactory::CreateComponent<AABBCollider>(other, 0.0f,0.0f,100.0f,100.0f);
    //ObjectFactory::CreateComponent<CircleCollider>(other, 100.0f);
    other->GetComponent<AABBCollider>()->SetTrigger(true);
    //other->GetComponent<CircleCollider>()->SetStatic(true);

    Entity* other2 = ObjectFactory::CreateEntity<Entity>(0);
    other2->GetTransform()->SetPosition(350.0f,350.0f);
    ObjectFactory::CreateComponent<AABBCollider>(other2, 0.0f,0.0f,100.0f,100.0f);
    //ObjectFactory::CreateComponent<CircleCollider>(other2, 100.0f);
    //other2->GetComponent<CircleCollider>()->SetStatic(true);
    other2->GetComponent<AABBCollider>()->SetStatic(true);

    Entity* camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);
    
}

void TestScene::OnUpdate()
{
    // std::cout << player->GetTransform()->position.x << std::endl;
    // std::cout << player->GetTransform()->position.y << std::endl;
}


