#pragma once

#include <SFML/Graphics.hpp>

#include "Shader.h"
#include "Sprite.h"

class SpriteSheet;

class RenderWindow final : public sf::RenderWindow
{
public:
    RenderWindow(std::string title, int width, int height, uint32_t style = sf::Style::Default, sf::State state = sf::State::Windowed);

    void BeginFrame();
    void Draw(Sprite* sprite);
    void Draw(SpriteSheet* sprite);
    void Draw(Sprite* sprite, Shader* shader);
    void Draw(const sf::Text* text);
    void Draw(sf::Shape* shape);
    void EndFrame();
    
    int GetWindowWidth();
    int GetWindowHeight();
};
