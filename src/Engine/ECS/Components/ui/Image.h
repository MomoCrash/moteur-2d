#pragma once

#include "ECS/Components/Component.h"

class Sprite;

class Image : public Component
{
public:
    static constexpr int BITMASK = 1 << 7;
    
    Image(Entity* entity, Sprite* uiImage);
    ~Image() override = default;
    int GetBitmask() override;

    Sprite* UIImage;
};
