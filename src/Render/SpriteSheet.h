#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "Sprite.h"

class Sprite;

class SpriteSheet : public sf::Sprite
{
    std::vector<sf::Vector2i> sprites;
    sf::Vector2i size;

public:
    SpriteSheet(Texture& sprite);
    
    void Extract(int startX, int startY, int singleWidth, int singleHeight, int width = 1, int height = 1);
    sf::Vector2i GetSpriteSheetPart(int index);
    void SetSpriteAt(sf::Vector2i offset);
    void SetSprite(int index);

    int SpriteCount;
};
