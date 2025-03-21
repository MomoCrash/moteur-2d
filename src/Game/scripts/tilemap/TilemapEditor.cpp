#include "pch.h"

#include "TilemapEditor.h"
#include "Transform.h"

#include "Resources.h"
#include "SpriteSheet.h"
#include "ECS/Components/Camera.h"
#include "ECS/Systems/CameraSystem.h"

TilemapEditor::TilemapEditor(const char* pathToResource, const char* outputFile) : mMainCamera(nullptr),
    mCameraPosition(nullptr), mTransform(nullptr), mSelector({32, 32}), mOffset({0, 0}), mTiles()
{
    strcat_s(pathToSpriteSheet, pathToResource);
    strcat_s(outputTilemap, outputFile);
}

void TilemapEditor::OnStart()
{

    mMainCamera = Engine::GetCameraSystem()->GetActiveCamera();
    mCameraPosition = &mMainCamera->GetEntity()->GetTransform()->position;
    
    mTransform = owner->GetTransform();
    mGridVertices = sf::VertexArray(sf::PrimitiveType::Triangles);

    mOffset.x = halfMapSize;
    mOffset.y = halfMapSize;

    mSelector.setFillColor(sf::Color::Red);

    
    Texture* tex = new Texture(std::string(pathToSpriteSheet), true);
    spriteSheet = new SpriteSheet(*tex);
    spriteSheet->Extract(0, 16, 16, 16, 160, 160);

    GenerateGrid();
    
}

void TilemapEditor::OnFixedUpdate()
{
    if (movement.x > tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({tileSize+.0f, 0.0f}));
        movement = {0, 0};
    } else if (movement.x < -tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({-tileSize+.0f, 0.0f}));
        movement = {0, 0};
    } else if (movement.y > tileSize) {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({0.f, tileSize+.0f}));
        movement = {0, 0};
    } else if (movement.y < -tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({0.f, -tileSize+.0f}));
        movement = {0, 0};
    }
}

void TilemapEditor::OnUpdate()
{
    mCurrentCase.x = (mousePosition.x/tileSize) * tileSize + mTransform->position.x + 2;
    mCurrentCase.y= (mousePosition.y/tileSize) * tileSize + mTransform->position.y + 2;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        int index = tilePerRow * (mCurrentCase.y/tileSize-2) + (mCurrentCase.x/tileSize-2);
       if (!mTiles.contains(index))
       {
           mTiles.emplace(index, Tile(spriteSheet->GetSpriteSheetPart(currentTileIndex), mCurrentCase));
       } else
       {
           mTiles.at(index).spriteSheetOffset = spriteSheet->GetSpriteSheetPart(currentTileIndex);
       }
    }

    // Movement on tile map
    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        movement += mTransform->right * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        movement -= mTransform->right * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        movement += mTransform->up * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        movement -= mTransform->up * Engine::GetDeltaTime() * 1000.0f;
    }

    // used to zoom out / in
    if (isKeyPressed(sf::Keyboard::Key::Subtract))
    {
        Engine::GetCameraSystem()->GetActiveCamera()->ZoomFactor += 1.0f * Engine::GetDeltaTime();
    }

    if (isKeyPressed(sf::Keyboard::Key::Add))
    {
        Engine::GetCameraSystem()->GetActiveCamera()->ZoomFactor -= 1.0f * Engine::GetDeltaTime();
    }

    if (GetKey(Keyboard::LControl) && GetKeyDown(Keyboard::S))
    {
        SaveGrid();
    }

    // used to navigate in tiles set
    bool isLeft = isKeyPressed(sf::Keyboard::Key::Left);
    bool isRight = isKeyPressed(sf::Keyboard::Key::Right);
    if (isLeft || isRight)
    {
        if (singlePress) return;
        if (isLeft)
            currentTileIndex = --currentTileIndex%spriteSheet->SpriteCount;
        if (isRight)
            currentTileIndex = ++currentTileIndex%spriteSheet->SpriteCount;
        singlePress = true;
    } else 
        singlePress = false;
    
}

void TilemapEditor::OnRender(RenderWindow* window)
{
    
    mousePosition = sf::Mouse::getPosition(*window);
    mSelector.setPosition(sf::Vector2f(mCurrentCase));
    window->draw(mSelector);
    window->draw(mGridVertices);

    for (auto& sprite : mTiles)
    {
        spriteSheet->SetSpriteAt(sprite.second.spriteSheetOffset);
        spriteSheet->setPosition(sf::Vector2f(sprite.second.position));
        window->Draw(spriteSheet);
    }

    int startIndex = currentTileIndex-8 < 0 ? 0 : currentTileIndex-8;
    int position = 0;
    for (int i = startIndex; i < spriteSheet->SpriteCount && i < currentTileIndex+8; i++)
    {
        sf::Vector2f finalPosition = sf::Vector2f(20 + (tileSize*2.0f + 10.0f) * position , 850.0f) + *mCameraPosition;
        if (i == currentTileIndex)
        {
            mSelector.setPosition(finalPosition - sf::Vector2f(3.0f, 3.0f));
            mSelector.scale({1.2f, 1.2f});
            window->draw(mSelector);
            mSelector.setScale({1.0f,1.0f});
        }
        spriteSheet->SetSprite(i);
        spriteSheet->setPosition(finalPosition);
        spriteSheet->setScale({2.0f, 2.0f});
        window->Draw(spriteSheet);
        position++;
    }
    
}

void TilemapEditor::GenerateGrid()
{
    for (int x = 0; x <= tilePerRow; x++)
    {
        int tileX = x * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, mapSize), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, mapSize), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, mapSize), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, 0), sf::Color::White));
    }
    
    for (int y = 0; y <= tilePerRow; y++) {
        int tileY = y * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+2), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY+2), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+2), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));
    }
    
}

void TilemapEditor::SaveGrid()
{
    std::filesystem::create_directories("../../res/Tiles/saved/");
    std::string toWrite;
    for (auto& tile : mTiles)
    {
        sf::Vector2i tilePosition = tile.second.position;
        sf::Vector2i spriteSheetOffset = tile.second.spriteSheetOffset;
        toWrite += "t " + std::to_string(tilePosition.x) + " "
            + std::to_string(tilePosition.y) + " "
            + std::to_string(spriteSheetOffset.x) + " "
            + std::to_string(spriteSheetOffset.y) + "\n";
    }
    std::string path(pathToSpriteSheet);
    toWrite += "spritesheet_path " + path;
    
    std::ofstream saveFile("../../res/Tiles/saved/scene0.txt");
    saveFile << toWrite;
    saveFile.close();
}
