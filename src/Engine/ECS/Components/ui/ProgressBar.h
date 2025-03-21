#pragma once
#include "ECS/Components/Component.h"

class Sprite;

class ProgressBar: public Component
{
public:
    static constexpr int BITMASK = 1 << 15;
    
    ProgressBar(Entity* entity, Sprite* background, Sprite* barImage, sf::Vector2f position = {0.0f, 0.0f}, sf::Vector2f barOffset = {0.0f, 0.0f});
    ~ProgressBar() override = default;
    int GetBitmask() override;

    Sprite* BackgroundImage;
    Sprite* Bar;

    sf::Vector2f ScreenPosition;
    sf::Vector2f BarOffset;
    
    float Progress;
    float Maximum;
};
