#include "Headers/Tile.h"

Tile::Tile(int xPos, int yPos, unsigned int weight, unsigned int height):
    x(xPos),
    y(yPos),
    Weight(weight),
    Height(height)
    {

    }

Tile::Tile():
    x(0),
    y(0),
    Weight(0),
    Height(0)
    {

    }