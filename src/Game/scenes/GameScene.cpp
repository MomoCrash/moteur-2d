#include "pch.h"
#include "GameScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/RigidBody2D.h"

#include "scripts/PlayerMovement.h"

void GameScene::OnEnter()
{

    srand(static_cast<unsigned int>(time(nullptr)));
    
    Resources* resources = &Resources::instance();
    
    resources->CreateShaders();
    resources->CreateParticles();
    resources->CreateTextures();
    resources->CreateMaterials();
    
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, 150.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().TEXTURE);
    ObjectFactory::CreateComponent<RigidBody2D>(player);
    player->SetTag(Entity::Tag::PLAYER);


    ObjectFactory::AttachScript<PlayerMovement>(player);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>(player);
    ObjectFactory::CreateComponent<Camera>(camera);
    
}

void GameScene::OnUpdate()
{

}