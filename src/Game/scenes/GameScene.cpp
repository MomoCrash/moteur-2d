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
#include "scripts/MusicScript.h"
#include "scripts/resources/Craft.h"

void GameScene::OnEnter()
{

    srand(static_cast<unsigned int>(time(nullptr)));
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, 0.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    player->SetTag(Entity::Tag::PLAYER);
    
    //ObjectFactory::AttachScript<MusicScript>(player);
    ObjectFactory::AttachScript<PlayerMovement>(player);
    Inventory* inventory = ObjectFactory::AttachScript<Inventory>(player);
    ObjectFactory::AttachScript<Craft>(player, inventory);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Camera>(camera);

    Entity* expBar = ObjectFactory::CreateEntity<Entity>();
    ObjectFactory::CreateComponent<Image>(expBar, Resources::instance().DEFAULT_SPRITE);
    
}

void GameScene::OnUpdate()
{

}