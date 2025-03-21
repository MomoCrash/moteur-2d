/// Made by Necxels 19/03/2025 
/// Thanks to him 

#include "pch.h"
#include "Inputs.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Keyboard.h"
#include "Mouse.h"


Inputs::State Inputs::s_keysStates[Keyboard::KEYCOUNT] {};
Inputs::State Inputs::s_buttonsStates[Mouse::BUTTONCOUNT] {};


void Inputs::UpdateKeyboard()
{
    for ( unsigned __int8 i = 0; i < Keyboard::KEYCOUNT; i++ )
        s_keysStates[i] =
            sf::Keyboard::isKeyPressed( static_cast<sf::Keyboard::Key>(i) ) ?
            (s_keysStates[i] & Pressed ? Pressed : Down ) :
            (s_keysStates[i] & Pressed ? Up : None );
}

void Inputs::UpdateMouse()
{
    for ( unsigned __int8 i = 0; i < Mouse::BUTTONCOUNT; i++ )
        s_buttonsStates[i] =
            sf::Mouse::isButtonPressed( static_cast<sf::Mouse::Button>(i) ) ?
            (s_buttonsStates[i] & Pressed ? Pressed : Down ) :
            (s_buttonsStates[i] & Pressed ? Up : None );
}