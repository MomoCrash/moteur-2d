#include "pch.h"
#include "ECS.h"

#include "Entity.h"
#include "Engine.h"
#include "Components/Component.h"

#include "scripts/ScriptManager.h"
#include "Systems/CameraSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/ParticleSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/RenderSystem.h"

ECS::ECS(): mEntityCount(0), mEntityToAddCount(0), mEntityToRemoveCount(0)
{
}

ECS::~ECS()
{
    for (int i = 0; i < mEntityCount; i++)
    {
        for (Component* component : mEntities[i]->AttachedComponents)
        {
            delete component;
        }
        delete mEntities[i]->Entity;
        delete mEntities[i];
    }
    mEntityCount = 0;
    
    for (int i = 0; i < mEntityToAddCount; i++)
    {
        for (Component* component : mToAddEntities[i]->AttachedComponents)
        {
            delete component;
        }
        delete mToAddEntities[i]->Entity;
    }
    mEntityToAddCount = 0;
    
}

void ECS::FixedUpdate()
{

    Engine::GetScriptManager()->OnFixedUpdate();

    Engine::GetPhysicsSystem()->OnFixedUpdate(this);
    Engine::GetCollisionSystem()->OnFixedUpdate(this);
    
}

void ECS::Update()
{

    for (int i = 0; i < mEntityToAddCount; i++)
    {
        EC* toAddEC = mToAddEntities[i];
        
        mEntities[mEntityCount] = toAddEC ;
        toAddEC->Entity->Create(mEntityCount);
        mEntityCount++;

        int layer = toAddEC->Entity->GetLayer();

        if(!mEntitiesByLayer.contains(layer))
        {
            mEntitiesByLayer[layer] = new std::list<Entity*>;
        }
        mEntitiesByLayer[layer]->push_back(toAddEC->Entity);
    }
    mEntityToAddCount = 0;

    for (int i = 0; i < mEntityToRemoveCount; i++)
    {
        int indexRemoved = *mToRemoveEntityIndex[i];

        mEntitiesByLayer[mEntities[indexRemoved]->Entity->GetLayer()]->remove(mEntities[indexRemoved]->Entity);
        if (indexRemoved == mEntityCount-1)
        {
            delete mEntities[indexRemoved];
            for (Component* component : mEntities[indexRemoved]->AttachedComponents)
            {
                delete component;
            }
            mEntityCount--;
            continue;
        }
        
        delete mEntities[indexRemoved]->Entity;
        for (Component* component : mEntities[indexRemoved]->AttachedComponents)
        {
            delete component;
        }
        delete mEntities[indexRemoved];
        mEntities[indexRemoved] = mEntities[mEntityCount-1];
        mEntities[indexRemoved]->Entity->SetIndex(indexRemoved);
        mEntityCount--;
        
    }
    mEntityToRemoveCount = 0;

    for (int i = 0; i < mEntityCount; i++)
    {
        Entity* entity = mEntities[i]->Entity;

        if (entity->IsDestroyed())
        {
            mToRemoveEntityIndex[mEntityToRemoveCount] = entity->GetIndex();
            mEntityToRemoveCount++;
            Engine::GetScriptManager()->RemoveEntity(entity->GetIndex());
            continue;
        }
    }
    
    Engine::GetCameraSystem()->Update(this);
    Engine::GetScriptManager()->OnUpdate();

    
}

void ECS::Draw()
{
    Engine::GetScriptManager()->OnRender(Engine::GetRenderWindow());
    Engine::GetRenderSystem()->Render(this);
    Engine::GetParticleSystem()->Render(this);
}
