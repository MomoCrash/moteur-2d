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
            image->UIImage->setPosition(cameraTransform->position + image->ScreenPosition);
            window->Draw(image->UIImage);
        }
        if (globalEC->HasComponent<Button>(i))
        {
            Button* button = globalEC->GetComponent<Button>(i);
            sf::Vector2f currentPosition = cameraTransform->position + button->ScreenPosition;
            button->UIImage->setPosition(currentPosition);
            window->Draw(button->UIImage);
            sf::Vector2f mClickPosition = sf::Vector2f(sf::Mouse::getPosition()) + currentPosition;

            if (!(mClickPosition.x < currentPosition.x
                || mClickPosition.x > currentPosition.x + button->Width
                || mClickPosition.y > currentPosition.y
                || mClickPosition.y < currentPosition.y + button->Height)) {
                button->CallBack();
            }
        }
        if (globalEC->HasComponent<ProgressBar>(i))
        {
            ProgressBar* progressBar = globalEC->GetComponent<ProgressBar>(i);
            progressBar->BackgroundImage->setPosition(cameraTransform->position + progressBar->ScreenPosition);
            progressBar->Bar->setPosition(cameraTransform->position + progressBar->ScreenPosition + progressBar->BarOffset);
            progressBar->Bar->setScale({progressBar->Progress/progressBar->Maximum, 1.0f});
            window->Draw(progressBar->BackgroundImage);
        }
    }
}