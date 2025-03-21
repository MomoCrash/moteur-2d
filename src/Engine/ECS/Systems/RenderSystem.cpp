#include "pch.h"
#include "RenderSystem.h"

#include <ranges>

#include "CameraSystem.h"
#include "Transform.h"
#include "ECS/ECS.h"
#include "../Components/SpriteRenderer.h"
#include "ECS/Components/Collider2D.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/ui/Image.h"
#include "Render/RenderWindow.h"

RenderSystem::RenderSystem(RenderWindow* window): window(window) {}

void RenderSystem::Render(ECS* globalEC)
{
    TRANSFORM* cameraTransform = Engine::GetCameraSystem()->GetActiveCamera()->GetEntity()->GetTransform();
    for (auto const& entity : std::views::values(globalEC->mEntitiesByLayer))
    {
        for(Entity* entities : *entity)
        {
            if (globalEC->HasComponent<SpriteRenderer>(entities->GetId()))
            {
                SpriteRenderer* renderer = globalEC->GetComponent<SpriteRenderer>(entities->GetId());
                sf::Vector2f size = renderer->Image->getGlobalBounds().size * 0.5f;
                TRANSFORM* transform = renderer->GetEntity()->GetTransform();
                renderer->Image->setPosition(transform->position - size);
                renderer->Image->setScale(transform->scale);
                renderer->Image->setRotation(transform->rotation);
            
                if (!renderer->RendererShader)
                    window->Draw(renderer->Image);
                else
                    window->Draw(renderer->Image, renderer->RendererShader);
            } else if (globalEC->HasComponent<Image>(entities->GetId()))
            {
                Image* image = globalEC->GetComponent<Image>(entities->GetId());
                image->UIImage->setPosition(cameraTransform->position);
                window->Draw(image->UIImage);
            }

            if(globalEC->HasComponent<Collider2D>(entities->GetId()))
            {
                Collider2D* coll = globalEC->GetComponent<Collider2D>(entities->GetId());
                window->Draw(coll->GetShape());
            }
        }
    }
}