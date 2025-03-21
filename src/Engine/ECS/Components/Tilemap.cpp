#include "pch.h"
#include "Tilemap.h"

#include <fstream>

#include "Utils/Debug.h"

class Debug;

Tilemap::Tilemap(Entity* entity, std::string pathToTilemap) : Component(entity)
{

    std::string path;
    std::vector<sf::Vector2f> position;
    std::vector<sf::Vector2f> spriteSheetOffset;
    
    std::string line;
    std::ifstream myfile(pathToTilemap);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::istringstream in(line);
            std::string type;
            in >> type;

            if (type == "t")
            {
                float x, y, offX, offY;
                in >> x >> y >> offX >> offY;

                position.push_back({x, y});
                spriteSheetOffset.push_back({offX, offY});
            }
            else if (type == "spritesheet_path")
            {
                in >> path;
            }
        }
        myfile.close();
    }
    
    for (int i = 0; i < position.size(); i++)
    {
        sf::Vector2f pos = position[i];
        sf::Vector2f offset = spriteSheetOffset[i];

        Debug::Log(std::to_string(position[i].x));
        
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offset));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x+16, pos.y), sf::Color::White, offset));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x+16, pos.y + 16), sf::Color::White, offset));
            
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 16), sf::Color::White, offset));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x+16, pos.y + 16), sf::Color::White, offset));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offset));
    }
    
}

int Tilemap::GetBitmask()
{
    return BITMASK;
}
