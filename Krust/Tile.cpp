#include "Headers/Tile.hpp"
#include "Headers/Cardinals.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>
#define OUT

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

double Tile::GetDistance(Tile* tile, int mapWidth, OUT bool& inverted){
    return GetDistance(tile->x, tile->y, mapWidth, inverted);
}

double Tile::GetDistance(int tileX, int tileY, int mapWidth, OUT bool& inverted){
    double dx = tileX - x;
    double dy = tileY - y;
    double d0 = std::sqrt(dx * dx + dy * dy);
    double d1 = std::sqrt((dx + mapWidth) * (dx + mapWidth) + dy * dy);
    if(d1 < d0){
        inverted = true;
        return d1;
    }
    else{
        inverted = false;
        return d0;
    }

}

float Tile::GetRadians_diff(Tile* tile) {
    return GetRadians_diff(tile->x, tile->y);
}

float Tile::GetRadians_diff(int tileX, int tileY) {
    glm::vec2 v1(x, y);
    glm::vec2 v2(tileX, tileY);
    return glm::angle(v1, v2);
}

glm::ivec2 Tile::GetDirection(Tile* tile, bool inverted){
    return GetDirection(tile->x, tile->y, inverted);
}

glm::ivec2 Tile::GetDirection(int tileX, int tileY, bool inverted) {
    glm::vec2 v1(x, y);
    glm::vec2 v2(tileX, tileY);
    glm::vec2 normalized_v = inverted? glm::normalize(v2 - v1) : glm::normalize(v1 - v2);
    glm::vec2 direction(0,0);
    if (normalized_v.x > 0.5) {
        direction.x = 1;
    } else if (normalized_v.x < -0.5) {
        direction.x = -1;
    }
    if (normalized_v.y > 0.5) {
        direction.y = 1;
    } else if (normalized_v.y < -0.5) {
        direction.y = -1;
    }
    return direction;
}