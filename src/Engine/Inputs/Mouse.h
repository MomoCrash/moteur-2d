#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

namespace Mouse {


enum Button: unsigned __int8 {
    Left,
    Right,
    Middle,
    Extra1,
    Extra2,
    BUTTONCOUNT,
};


[[nodiscard]] bool GetButton( Button const button );
[[nodiscard]] bool GetButtonUp( Button const button );
[[nodiscard]] bool GetButtonDown( Button const button );


}

#endif