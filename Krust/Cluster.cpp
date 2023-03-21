#include "Headers/Cluster.hpp"
#include <vector>
#include "FastNoiseLite.h"

Cluster::Cluster(int identifier, int centerX, int centerY, FastNoiseLite noise, bool terrestial):
    CenterX(centerX),
    CenterY(centerY),
    Identifier(identifier),
    Noise(noise),
    Terrestial(terrestial)
    {
        
    }

Cluster::Cluster():
    CenterX(0),
    CenterY(0),
    Identifier(0),
    Noise(FastNoiseLite())
    {

    }

float Cluster::FindShortestPath(Tile start, int mapWidth){
    return FindShortestPath(start.x,start.y, mapWidth);
}

float Cluster::FindShortestPath(int startX, int startY, int mapWidth){
    return FindShortestPath(glm::vec2(startX, startY), mapWidth);
}

float Cluster::FindShortestPath(glm::vec2 start, int mapWidth){
    auto inverted = false;
    auto distance = static_cast<float>(GetDistance(start, mapWidth, inverted));
    if(inverted) start.x += mapWidth;
    glm::vec2 delta = start - glm::vec2(CenterX, CenterY);
    float angle = atan2(delta.y, delta.x);
    float noise = Noise.GetNoise(static_cast<float>(40 * cos(angle)),static_cast<float>(40 * sin(angle)), 0.0f);
    auto weightValue = (1.0f + (noise / 3));
    return distance * weightValue;
}

double Cluster::GetDistance(Tile start, int mapWidth, OUT bool inverted){
    return GetDistance(glm::vec2(start.x, start.y), mapWidth, inverted);
}

double Cluster::GetDistance(int startX, int startY, int mapWidth, OUT bool inverted){
    return GetDistance(glm::vec2(startX, startY), mapWidth, inverted);
}

double Cluster::GetDistance(glm::vec2 start, int mapWidth, OUT bool inverted){
    double dx = start.x - CenterX;
    double dy = start.y - CenterY;
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
