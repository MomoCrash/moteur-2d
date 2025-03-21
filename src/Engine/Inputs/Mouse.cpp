/// Made by Necxels 19/03/2025 
/// Thanks to him 

#include "pch.h"
#include "Mouse.h"

#include "Inputs.h"

namespace Mouse {


[[nodiscard]] bool GetButton( Button const button ) { return Inputs::s_buttonsStates[button] & Inputs::State::Pressed; }

[[nodiscard]] bool GetButtonUp( Button const button ) { return Inputs::s_buttonsStates[button] == Inputs::State::Up; }

[[nodiscard]] bool GetButtonDown( Button const button ) { return Inputs::s_buttonsStates[button] == Inputs::State::Down; }


}