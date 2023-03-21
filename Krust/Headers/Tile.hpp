#pragma once
#include <map>

struct Tile{
    Tile(int xPos, int yPos, unsigned int height);
    Tile();
    int x;
    int y;

    double Height;
    unsigned long ClusterIndex;
};
