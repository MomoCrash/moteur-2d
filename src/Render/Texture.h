#pragma once

#include <SFML/Graphics/Texture.hpp>

class Texture : public sf::Texture
{
public:
    Texture(std::string path, bool customPath=false);
    std::string path;
};
