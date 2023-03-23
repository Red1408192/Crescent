#include "Headers/Cluster.hpp"
#include <vector>
#include "FastNoiseLite.h"

Cluster::Cluster(int identifier, int centerX, int centerY, int seed, bool terrestial):
    CenterX(centerX),
    CenterY(centerY),
    Identifier(identifier),
    Terrestial(terrestial)
    {
        FastNoiseLite noise(seed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise.SetFrequency(0.010);
        noise.SetFractalGain(0.7f);
        noise.SetFractalOctaves(6);
        noise.SetFractalLacunarity(1.9f);
        Noise = noise;
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
    auto inverted = 0;
    auto distance = static_cast<float>(GetDistance(start, mapWidth, inverted));
    if(inverted == 1) start.x += mapWidth;
    if(inverted == 2) start.x -= mapWidth;
    glm::vec2 delta = start - glm::vec2(CenterX, CenterY);
    float angle = atan2(delta.y, delta.x);
    float noise = Noise.GetNoise(static_cast<float>(40 * cos(angle)),static_cast<float>(40 * sin(angle)), 0.0f);
    auto weightValue = (1.0f + (noise / 6));
    return distance * weightValue;
}

double Cluster::GetDistance(Tile start, int mapWidth, OUT char inverted){
    return GetDistance(glm::vec2(start.x, start.y), mapWidth, inverted);
}

double Cluster::GetDistance(int startX, int startY, int mapWidth, OUT char inverted){
    return GetDistance(glm::vec2(startX, startY), mapWidth, inverted);
}

double Cluster::GetDistance(glm::vec2 start, int mapWidth, OUT char inverted){
    double dx = start.x - CenterX;
    double dy = start.y - CenterY;
    double d0 = std::sqrt(dx * dx + dy * dy);
    double d1 = std::sqrt((dx + mapWidth) * (dx + mapWidth) + dy * dy);
    double d3 = std::sqrt((dx - mapWidth) * (dx - mapWidth) + dy * dy);
    if(d1 < d0){
        inverted = 1;
        return d1;
    }
    else if(d3 < d0){
        inverted = 2;
        return d3;
    }
    else{
        inverted = 0;
        return d0;
    }
}
