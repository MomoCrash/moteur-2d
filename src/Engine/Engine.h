﻿#pragma once
#include <windows.h>

class RenderWindow;
class ScriptManager;
class ParticleSystem;
class CollisionSystem;
class PhysicsSystem;
class CameraSystem;
class RenderSystem;
class ECS;
class InputManager;
class GameManager;
class ObjectFactory;

class Engine
{
public:
    Engine();
    ~Engine();

    static void SetRenderWindow(HINSTANCE instance);
    static RenderWindow* GetRenderWindow();
    
    static GameManager* GetGameManager();
    static InputManager* GetInputManager();
    
    static float GetDeltaTime();

private:
    static Engine& instance()
    {
        static Engine game;
        return game;
    }

    static ECS* GetECS();
    static RenderSystem* GetRenderSystem();
    static CameraSystem* GetCameraSystem();
    static PhysicsSystem* GetPhysicsSystem();
    static CollisionSystem* GetCollisionSystem();
    static ParticleSystem* GetParticleSystem();
    static ScriptManager* GetScriptManager();

    GameManager* mGameManager;

    ECS* mECS;
    RenderSystem* mRenderSystem;
    PhysicsSystem* mPhysicsSystem;
    CollisionSystem* mCollisionSystem;
    CameraSystem* mCameraSystem;
    ParticleSystem* mParticleSystem;
    ScriptManager* mScriptManager;
    InputManager* mInputManager;

    RenderWindow* mRenderWindow;

    // Make system only accessible from engine
    friend class Entity;
    friend class ECS;
    
    friend class ObjectFactory;
    
    friend class GameManager;
    friend class RenderSystem;
    friend class PhysicsSystem;
    friend class CollisionSystem;
    friend class CameraSystem;
    friend class ScriptManager;
};
