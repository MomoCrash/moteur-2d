#pragma once

#include <map>

#include "scripts/Script.h"

class Camera;
class SpriteSheet;

struct Tile
{
    sf::Vector2i spriteSheetOffset;
    sf::Vector2i position;
};

class TilemapEditor : public IScript
{
public:
    TilemapEditor(const char* pathToResource, const char* outputFile);
    void OnStart() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
    void OnRender(RenderWindow* window) override;
    
    void GenerateGrid();
    void SaveGrid();

private:

    Camera* mMainCamera;
    sf::Vector2f* mCameraPosition;
    TRANSFORM* mTransform;
    sf::Vector2f movement;
    
    sf::Vector2i mousePosition;
    bool singlePress = false;

    sf::VertexArray mGridVertices;
    sf::RectangleShape mSelector;
    sf::Vector2i mCurrentCase;
    sf::Vector2i mOffset;

    int currentTileIndex = 8;
    std::vector<Tile> tileMap;
    SpriteSheet* spriteSheet = nullptr ;
    std::map<int, Tile> mTiles;

    char pathToSpriteSheet[50];
    char outputTilemap[50];

    // Configuration of current tileset editor (Grid is just visual you can draw out of the grid)
    static constexpr int mapSize = 10000;
    static constexpr int halfMapSize = mapSize/2;
    static constexpr int tileSize = 32;
    static constexpr int tilePerRow = mapSize/tileSize;
    static constexpr int totalTile = tilePerRow*tilePerRow;
};
