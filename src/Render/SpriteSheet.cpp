#include "SpriteSheet.h"

#include "Sprite.h"
#include "Texture.h"

SpriteSheet::SpriteSheet(Texture& spriteSheet) : Sprite(spriteSheet), SpriteCount(0)
{
}

void SpriteSheet::Extract(int startX, int startY, int singleWidth, int singleHeight, int width, int height)
{

    size.x = singleWidth;
    size.y = singleHeight;

    for (int x = startX; x < startX+width; x+=singleWidth)
    {
        for (int y = startY; y < startY+height; y+=singleHeight)
        {
            sprites.push_back( {x, y} );
            SpriteCount++;
        }
    }
    
}

sf::Vector2i SpriteSheet::GetSpriteSheetPart(int index)
{
    return sprites[index];
}

void SpriteSheet::SetSpriteAt(sf::Vector2i offset)
{
    setTextureRect({offset, size});
}

void SpriteSheet::SetSprite(int index)
{
    setTextureRect({sprites[index], size});
}
