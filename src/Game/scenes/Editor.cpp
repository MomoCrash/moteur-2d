#include "pch.h"
#include "Editor.h"

#include "Resources.h"
#include "ECS/Entity.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/SpriteRenderer.h"
#include "ECS/Components/Tilemap.h"

void Editor::OnEnter()
{

    Entity* gridContainer = ObjectFactory::CreateEntity<Entity>();
    gridContainer->GetTransform()->SetPosition(0.0f, 0.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(gridContainer, Resources::instance().DEFAULT_SPRITE);

    /*ObjectFactory::AttachScript<TilemapEditor>(gridContainer,
        "../../res/Tiles/tileset.png",
        "../../res/Tiles/saved/scene0.png");*/

    //ObjectFactory::CreateComponent<Tilemap>(gridContainer, "../../res/Tiles/saved/scene0.txt");
    
    Entity* player = ObjectFactory::CreateEntity<Entity>();
    player->GetTransform()->SetPosition(0.0f, 0.0f);
    ObjectFactory::CreateComponent<SpriteRenderer>(player, Resources::instance().DEFAULT_SPRITE);
    player->SetTag(Entity::Tag::PLAYER);
    
    Entity* camera = ObjectFactory::CreateEntity<Entity>(gridContainer);
    ObjectFactory::CreateComponent<Camera>(camera);
    
}

void Editor::Render()
{
    
}
