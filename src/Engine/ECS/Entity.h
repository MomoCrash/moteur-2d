#pragma once
#include <cstdint>

struct TRANSFORM;

class Entity
{
public:
    Entity(int layer = 0);
    Entity(Entity* parent, int layer = 0);
    ~Entity();

    enum class Tag : uint8_t
    {
        NONE,
        PLAYER,
        GROUND,
        OBSTACLE,
        ENNEMY,
        PROJECTILES,
        ENEMY_PROJECTILES,
        BUMPER,

        TAG_COUNT
    };

    
    template<typename T>
    T* GetComponent();
    template<typename T>
    bool HasComponent() const;

    void AddBitmask(int mask);
    void RemoveBitmask(int mask);
    void SetIndex(int index);
    int GetId();
    int* GetIndex();

    void Create(int index);
    void Destroy();

    bool IsCreated() const;
    bool IsDestroyed() const;
    
    void SetTag(Tag nTag) { mTag = nTag; }
    bool IsTag(Tag oTag) const { return mTag == oTag; }
    [[nodiscard]] Tag GetTag() const { return mTag; }

    int GetLayer() const { return mLayer; }
    void SetLayer(int nLayer) { mLayer = nLayer; }
    
    TRANSFORM* GetTransform() const {return mTransform; }
    int Bitmask;

protected:
    bool mCreated;
    bool mDestoyed;
    int mId;
    int mIndex;
    int mLayer;
    Tag mTag;
    
private:
    TRANSFORM* mTransform;
    static int sNextId;
};

#include "Entity.inl"