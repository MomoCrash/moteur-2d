#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Texture;

class Sprite : public sf::Sprite
{
public:
    Sprite(Texture& sprite);
    Sprite(sf::Sprite& sprite);
    ~Sprite() override = default;
    
    void SetAlpha(uint8_t alpha);
    
    Sprite* Cut(int x, int y, int width, int height);
};
