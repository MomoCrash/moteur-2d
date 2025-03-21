#include "pch.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(Entity* entity, Sprite* background, Sprite* progressBar) :
    Component(entity), Bar(progressBar), BackgroundImage(background)
{
    
}

int ProgressBar::GetBitmask()
{
    return BITMASK;
}

void ProgressBar::SetPercent(float percent)
{
    pe
}
