#ifndef INPUTS_H_INCLUDED
#define INPUTS_H_INCLUDED

namespace Keyboard { enum Key: unsigned __int8; }
namespace Keyboard { bool GetKey( Key key ); }
namespace Keyboard { bool GetKeyUp( Key key ); }
namespace Keyboard { bool GetKeyDown( Key key ); }
namespace Mouse { enum Button: unsigned __int8; }
namespace Mouse { bool GetButton( Button button ); }
namespace Mouse { bool GetButtonUp( Button button ); }
namespace Mouse { bool GetButtonDown( Button button ); }


class Inputs
{
    static void UpdateKeyboard();
    static void UpdateMouse();

    enum State: unsigned __int8 {
        None    = 0b000,
        Up      = 0b100,
        Down    = 0b001,
        Pressed = 0b011,
    };

    static State s_keysStates[];
    static State s_buttonsStates[];
    
    friend bool Keyboard::GetKey( Keyboard::Key key );
    friend bool Keyboard::GetKeyUp( Keyboard::Key key );
    friend bool Keyboard::GetKeyDown( Keyboard::Key key );
    friend bool Mouse::GetButton( Mouse::Button button );
    friend bool Mouse::GetButtonUp( Mouse::Button button );
    friend bool Mouse::GetButtonDown( Mouse::Button button );

    friend class GameManager;
};


#endif