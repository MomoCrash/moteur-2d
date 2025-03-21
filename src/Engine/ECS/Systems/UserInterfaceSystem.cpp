#include "pch.h"
#include "UserInterfaceSystem.h"

#include "CameraSystem.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/Button.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/ui/ProgressBar.h"
#include "Render/RenderWindow.h"
#include "Render/Sprite.h"

UserInterfaceSystem::UserInterfaceSystem(RenderWindow* window): window(window) {}

void UserInterfaceSystem::Render(ECS* globalEC)
{
    TRANSFORM* cameraTransform = Engine::GetCameraSystem()->GetActiveCamera()->GetEntity()->GetTransform();
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (globalEC->HasComponent<Image>(i))
        {
            Image* image = globalEC->GetComponent<Image>(i);
            image->UIImage->setPosition(cameraTransform->position);
            window->Draw(image->UIImage);
        }
        /*if (globalEC->HasComponent<Button>(i))
        {
            Button* button = globalEC->GetComponent<Button>(i);
            button-> ->setPosition(cameraTransform->position);
            window->Draw(button->UIImage);
        }
        if (globalEC->HasComponent<ProgressBar>(i))
        {
            ProgressBar* button = globalEC->GetComponent<ProgressBar>(i);
            button-> ->setPosition(cameraTransform->position);
            window->Draw(button->UIImage);
        }*/
    }
}