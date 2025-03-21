#pragma once

#include <map>
#include <vector>

class Component;
class Entity;

struct EC
{
    Entity* Entity;
    std::vector<Component*> AttachedComponents;
};

class ECS
{
public:

    ECS();
    ~ECS();

    template <typename Type, typename ... Args>
    Type* CreateEntity(Args&&... args);

    void Update();
    void FixedUpdate();
    void Draw();

    Entity* GetEntity(int index) { return mEntities[index]->Entity; }
    
    template <typename T, typename... Args>
    T* AddComponent(Entity* entity, Args&&... args);
    template<typename T>
    T* GetComponent(Entity* entity);
    template<typename T>
    T* GetComponent(int entityIndex);
    template<typename T>
    bool HasComponent(int entityIndex) const;

    int mEntityCount;
    int mEntityToAddCount;
    int mEntityToRemoveCount;
    std::map<int, std::list<Entity*>*> mEntitiesByLayer;

private:
    EC** mEntities = new EC*[16000];
    EC** mToAddEntities = new EC*[1024];

    
    int** mToRemoveEntityIndex = new int*[512];
};

#include "ECS.inl"