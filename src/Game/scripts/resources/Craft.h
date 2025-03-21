#pragma once
#include "scripts/Script.h"

class Craft : public IScript
{
public:
    void OnStart() override;
    void OnUpdate() override;
};
