#ifndef PCH_H
#define PCH_H

#include <SFML/Graphics.hpp>

#include "Render/Texture.h"
#include "Render/Sprite.h"
#include "Render/RenderWindow.h"
#include "Resources.h"

#include <windows.h>
#include <iostream>

#include <sstream>
#define CONSOLE_OUTPUT(s) { std::wostringstream os_; os_ << s; OutputDebugStringW(os_.str().c_str());};


#include "Utils/Debug.h"
#include "Utils/Profiler.h"

#include <sstream>
#define CONSOLE_OUTPUT(s) { std::wostringstream os_; os_ << s; OutputDebugStringW(os_.str().c_str());};

#endif