#include "pch.h"
#include "Button.h"

Button::Button(Entity* entity, Sprite* sprite, std::function<void()> buttonAction, sf::Vector2f position, int width, int height): Component(entity),
    UIImage(sprite), CallBack(buttonAction), ScreenPosition(position), Width(width), Height(height)
{
}

int Button::GetBitmask()
{
    return BITMASK;
}
