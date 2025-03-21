#include "RenderWindow.h"

#include "Colors.h"
#include "Sprite.h"
#include "SpriteSheet.h"

RenderWindow::RenderWindow(const std::string title, const int width, const int height, uint32_t style, sf::State state)
: sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), title, style, state)
{}

void RenderWindow::BeginFrame()
{
    clear(Colors::blue);
}

void RenderWindow::Draw(Sprite* sprite)
{
    draw(*sprite);
}

void RenderWindow::Draw(SpriteSheet* sprite)
{
    draw(*sprite);
}

void RenderWindow::Draw(Sprite* sprite, Shader* shader)
{
    sf::RenderStates state = sf::RenderStates::Default;
    state.shader = shader;
    state.texture = &sprite->getTexture();
    draw(*sprite, state);
}

void RenderWindow::Draw(const sf::Text* text)
{
    draw(*text);
}

void RenderWindow::Draw(sf::Shape* shape)
{
    draw(*shape);
}

void RenderWindow::EndFrame()
{
    display();
}

int RenderWindow::GetWindowWidth()
{
    return static_cast<int>(getSize().x);
}

int RenderWindow::GetWindowHeight()
{
    return static_cast<int>(getSize().y);
}