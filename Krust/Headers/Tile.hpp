#pragma once
#include <map>

struct Tile{
    Tile(int xPos, int yPos, unsigned int weight, unsigned int height);
    Tile();
    int x;
    int y;
    std::map<int, int> ClusterDistances;

    unsigned int Weight;
    unsigned int Height;
    unsigned long ClusterIndex;
    double GetDistance(Tile* tile);
    double GetDistance(int tileX, int tileY);
};
