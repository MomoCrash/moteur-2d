#include "Texture.h"

#include "Engine/Utils/Debug.h"

Texture::Texture(std::string name, bool customPath)
{
    path = (customPath ? "" : "../../res/Textures/") + name;
    if (!loadFromFile(path))
    {
        Debug::Error("La texture " + path + " was not found.");
    }
}
