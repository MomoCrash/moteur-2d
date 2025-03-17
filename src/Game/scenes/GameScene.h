#pragma once
#include "Managers/Scene.h"
#include "scripts/Inventory.h"
class GameScene : public Scene
{

private:
    void OnEnter() override;
    void OnExit() override {}
    void OnFixedUpdate() override {}
    void Render() override {}
    void OnUpdate() override;
    Inventory inventory;
};
