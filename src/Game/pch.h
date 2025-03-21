#ifndef PCH_H
#define PCH_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Render/Texture.h"
#include "Render/Sprite.h"
#include "Render/RenderWindow.h"

#include <windows.h>
#include <iostream>

#include <sstream>
#define CONSOLE_OUTPUT(s) { std::wostringstream os_; os_ << s; OutputDebugStringW(os_.str().c_str());};


#include "Utils/Debug.h"
#include "Utils/Profiler.h"

#endif