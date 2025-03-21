#include "pch.h"
#include "main.h"

#include "Engine.h"
#include "Resources.h"
#include "Managers/GameManager.h"

#include "scenes/Editor.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{

    srand(time(nullptr));
    
    Engine::CreateRender();

    Resources::instance().Initialize();
    
    Engine::GetGameManager()->LaunchScene<Editor>();
    
    return 0;
}
