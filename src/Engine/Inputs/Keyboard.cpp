/// Made by Necxels 19/03/2025 
/// Thanks to him 

#include "pch.h"
#include "Keyboard.h"

#include "Inputs.h"

namespace Keyboard {
    

bool GetKey( Key const key ) { return Inputs::s_keysStates[key] & Inputs::State::Pressed; }
    
bool GetKeyUp( Key const key ) { return Inputs::s_keysStates[key] == Inputs::State::Up; }
    
bool GetKeyDown( Key const key ) { return Inputs::s_keysStates[key] == Inputs::State::Down; }


}