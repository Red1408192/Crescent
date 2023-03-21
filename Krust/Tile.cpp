#include "Headers/Tile.hpp"
#include "Headers/Cardinals.hpp"
#include <cmath>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#define OUT

Tile::Tile(int xPos, int yPos, unsigned int height):
    x(xPos),
    y(yPos),
    Height(height)
    {

    }

Tile::Tile():
    x(0),
    y(0),
    Height(0)
    {

    }