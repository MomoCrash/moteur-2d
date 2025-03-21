#include "pch.h"
#include "Image.h"

Image::Image(Entity* entity, Sprite* uiImage, sf::Vector2f position) : Component(entity), ScreenPosition(position),
                                                                       UIImage(uiImage)
{
}

int Image::GetBitmask()
{
    return BITMASK;
}
