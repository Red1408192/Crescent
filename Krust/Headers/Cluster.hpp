#pragma once
#include <vector>
#include "Tile.hpp"
#include "../FastNoiseLite.h"
#include <glm/glm.hpp>
#define OUT

class Cluster{
    private:
    public:
    Cluster(int Identifier, int centerX, int centerY, int seed, bool terrestial);
    Cluster();
    int Identifier;
    FastNoiseLite Noise;
    int CenterX;
    int CenterY;
    bool Terrestial;

    float FindShortestPath(Tile start, int mapWidth);
    float FindShortestPath(int startX, int startY, int mapWidth);
    float FindShortestPath(glm::vec2 start, int mapWidth);
    double GetDistance(glm::vec2 start, int mapWidth, OUT char inverted);
    double GetDistance(int startX, int startY, int mapWidth, OUT char inverted);
    double GetDistance(Tile start, int mapWidth, OUT char inverted);
};