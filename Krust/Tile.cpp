#include "Headers/Tile.hpp"
#include <cmath>

Tile::Tile(int xPos, int yPos, unsigned int weight, unsigned int height):
    x(xPos),
    y(yPos),
    Weight(weight),
    Height(height),
    ClusterDistances()
    {

    }

Tile::Tile():
    x(0),
    y(0),
    Weight(0),
    Height(0)
    {

    }

double Tile::GetDistance(Tile* tile){
    auto yDist = (tile->y - y);
    auto xDist = (tile->x - x);

    return sqrt(yDist*yDist + xDist*xDist)/2;
}
double Tile::GetDistance(int tileX, int tileY){
    auto yDist = (tileY - y);
    auto xDist = (tileX - x);

    return sqrt(yDist*yDist + xDist*xDist)/2;
}