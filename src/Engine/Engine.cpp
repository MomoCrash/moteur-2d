#include "pch.h"
#include "Engine.h"

#include "ECS/Systems/CameraSystem.h"
#include "ECS/Systems/CollisionSystem.h"
#include "ECS/Systems/ParticleSystem.h"
#include "ECS/Systems/PhysicsSystem.h"
#include "ECS/Systems/RenderSystem.h"
#include "Managers/GameManager.h"
#include "scripts/ScriptManager.h"

#include "ECS/ECS.h"
#include "Render/RenderWindow.h"

Engine::Engine() : mGameManager(new GameManager()), mECS(new ECS()), mRenderSystem(nullptr),
                   mPhysicsSystem(new PhysicsSystem()), mCollisionSystem(new CollisionSystem()), mCameraSystem(nullptr),
                   mParticleSystem(nullptr),
                   mScriptManager(new ScriptManager()),
                   mRenderWindow(nullptr)
{
}

Engine::~Engine()
{
    delete mGameManager;

    delete mECS;
    delete mRenderSystem;
    delete mPhysicsSystem;
    delete mCollisionSystem;
    delete mCameraSystem;
    delete mParticleSystem;
    delete mScriptManager;

    delete mRenderWindow;
}


void Engine::CreateRender()
{
    RenderWindow* window = instance().mRenderWindow;
    if (window) return;
    
    window = new RenderWindow("La window", 1600, 900);
    
    instance().mCameraSystem = new CameraSystem(window);
    instance().mRenderSystem = new RenderSystem(window);
    instance().mParticleSystem = new ParticleSystem(window);

    instance().mRenderWindow = window;
}

GameManager* Engine::GetGameManager()
{
    return instance().mGameManager;
}

CameraSystem* Engine::GetCameraSystem()
{
    return instance().mCameraSystem;
}

RenderWindow* Engine::GetRenderWindow()
{
    return instance().mRenderWindow;
}

RenderSystem* Engine::GetRenderSystem()
{
    return instance().mRenderSystem;
}

PhysicsSystem* Engine::GetPhysicsSystem()
{
    return instance().mPhysicsSystem;
}

CollisionSystem* Engine::GetCollisionSystem()
{
    return instance().mCollisionSystem;
}

ParticleSystem* Engine::GetParticleSystem()
{
    return instance().mParticleSystem;
}

ScriptManager* Engine::GetScriptManager()
{
    return instance().mScriptManager;
}

float Engine::GetDeltaTime()
{
    return instance().mGameManager->GetTime()->GetDeltaTime();
}

ECS* Engine::GetECS()
{
    return instance().mECS;
}
