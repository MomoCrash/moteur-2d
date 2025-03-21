#pragma once
#include <functional>

#include "ECS/Components/Component.h"

class Sprite;

class Button : public Component
{
public:
    static constexpr int BITMASK = 1 << 17;
    
    Button(Entity* entity, Sprite* uiImage = nullptr, std::function<void()> buttonAction = nullptr, sf::Vector2f position = {0.0f, 0.0f}, int width = 50, int height = 50);
    ~Button() override = default;
    int GetBitmask() override;

    Sprite* UIImage;
    sf::Vector2f ScreenPosition;
    int Width;
    int Height;

   std::function<void()> CallBack;
};
