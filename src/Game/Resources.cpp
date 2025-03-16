#include "pch.h"
#include "Resources.h"

#include "Render/Sprite.h"
#include "Render/Texture.h"

Resources::~Resources()
{
}

void Resources::Initialize()
{
    Resources* resources = &instance();
    
    resources->CreateShaders();
    resources->CreateParticles();
    resources->CreateTextures();
    resources->CreateSprite();
    resources->CreateFonts();
}

void Resources::CreateShaders()
{
}

void Resources::CreateParticles()
{
}

void Resources::CreateTextures()
{
    DEFAULT_TEXTURE = new Texture("test.png");
}

void Resources::CreateSprite()
{
    DEFAULT_SPRITE = new Sprite(DEFAULT_TEXTURE);
}

void Resources::CreateFonts()
{
    if (!DEFAULT_FONT->loadFromFile("../../res/Fonts/arial.ttf"))
    {
        std::cout << "Error loading font" << "\n";
    }
}
