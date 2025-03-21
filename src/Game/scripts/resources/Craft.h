#pragma once
#include "scripts/Inventory.h"
#include "scripts/Script.h"

class Craft : public IScript
{

    enum CraftPattern
    {
        
    };
    
    Inventory* mInventory;
public:
    Craft(Inventory* inventory);
    
    void OnStart() override;
    void OnUpdate() override;
    void OnRender(RenderWindow* window) override;
};
