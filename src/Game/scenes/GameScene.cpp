#include "pch.h"
#include "GameScene.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/ui/Image.h"

#include "scripts/PlayerMovement.h"


void GameScene::OnEnter()
{

    srand(static_cast<unsigned int>(time(nullptr)));
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, -500.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    player->SetTag(Entity::Tag::PLAYER);
    
    ObjectFactory::AttachScript<PlayerMovement>(player);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);

    Entity* expBar = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Image>(expBar, Resources::instance().DEFAULT_SPRITE);

    
}

void GameScene::OnUpdate()
{

}