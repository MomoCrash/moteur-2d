#pragma once
#include "Component.h"

class Tilemap : public Component
{
public:
    static constexpr int BITMASK = 1 << 15;
    Tilemap(Entity* entity, std::string pathToTilemap);

    sf::VertexArray VertexArray;
    int GetBitmask() override;
};
