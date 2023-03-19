#pragma once
#include <map>
#include "Cardinals.hpp"
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/gtx/vector_angle.hpp>
#define OUT

struct Tile{
    Tile(int xPos, int yPos, unsigned int weight, unsigned int height);
    Tile();
    int x;
    int y;
    std::map<int, int> ClusterDistances;

    float Weight;
    unsigned int Height;
    unsigned long ClusterIndex;

    double GetDistance(Tile* tile, int mapWidth, OUT bool& c);
    double GetDistance(int tileX, int tileY, int mapWidth, OUT bool& c);

    float GetRadians_diff(int tileX, int tileY);
    float GetRadians_diff(Tile* tile);

    glm::ivec2 GetDirection(Tile* tile, bool inverted);
    glm::ivec2 GetDirection(int tileX, int tileY, bool inverted);
};
