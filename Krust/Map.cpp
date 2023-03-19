#include "Headers/Map.hpp"
#include "Headers/Cluster.hpp"
#include "Tile.cpp"
#include <vector>
#include <cstddef>
#include <cstdlib>
#include "FastNoiseLite.h"
#include "Headers/Cardinals.hpp"
#include <map>

Map::Map(int width, int height, int continents, int maxWeight, int seed):
    Matrix(height, std::vector<Tile>(width)),
    Height(height),
    Width(width),
    Continents(continents)
    {
        srand(seed);
        int currentContinentIndex = 0;
        std::vector<std::pair<int, int>> clusterCenters(continents);
        for (size_t i = 0; i < continents; i++)
        {
            clusterCenters[i] = std::pair<int, int>((rand()+1)%(height-1), (rand()+1)%(height-1));
        }
        FastNoiseLite noise(seed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFrequency(0.018f);
        int index = 0;

        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                Matrix[y][x] = Tile(x, y, (rand() % maxWeight), 1000);

                auto noiseValue = noise.GetNoise((float)x, (float)y);
                auto weight = 1.f + ( (noiseValue + 1) / 10 );
                Matrix[y][x].Weight = weight;
            }
        }
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                int currentShortestIndex = __INT_MAX__;
                int currentShortest = __INT_MAX__;
                for (size_t i = 0; i < continents; i++){
                    auto h = FindShortestPath(&Matrix[y][x], clusterCenters[i].second, clusterCenters[i].first);
                    Matrix[y][x].ClusterDistances[i] = h;

                    if(h == 0) this->Continents[currentContinentIndex++].CenterTile = &Matrix[y][x];
                    if(currentShortest > h){
                        currentShortestIndex = i;
                        currentShortest = h;
                    }
                }
                Matrix[y][x].ClusterIndex = currentShortestIndex;
            }
        }

    };

    int Map::FindShortestPath(Tile *start, Tile *end){
        return FindShortestPath(start, end->x, end->y);
    }
    
    int Map::FindShortestPath(Tile *start, int endX, int endY){
        auto inverted = false;
        auto distance = static_cast<int>(start->GetDistance(endX, endY, Width, inverted));
        auto direction = start->GetDirection(endX, endY, inverted);
        auto yIndex = 0;
        if(start->y == 0 && direction.y == -1) yIndex = start->y+Width+direction.y;
        else if(start->y == Width-1 && direction.y == 1) yIndex = start->y-Width-1+direction.y;
        auto weight1 = Matrix[yIndex][start->x+direction.x].Weight;
        auto weight2 = Matrix[endY-direction.y][endX-direction.x].Weight;
        return distance * weight1 *(weight2+0.5f);
    }
    Tile* Map::GetNorth(Tile* tile){
        return &Matrix[tile->y+1][tile->x];
    } 
    Tile* Map::GetSouth(Tile* tile){
        return &Matrix[tile->y-1][tile->x];
    } 
    Tile* Map::GetEast(Tile* tile){
        return &Matrix[tile->y][tile->x+1];
    } 
    Tile* Map::GetWest(Tile* tile){
        return &Matrix[tile->y][tile->x-1];
    } 
    Tile* Map::GetNorthEast(Tile* tile){
        return &Matrix[tile->y+1][tile->x+1];
    } 
    Tile* Map::GetNorthWest(Tile* tile){
        return &Matrix[tile->y+1][tile->x-1];
    } 
    Tile* Map::GetSouthEast(Tile* tile){
        return &Matrix[tile->y-1][tile->x+1];
    } 
    Tile* Map::GetSouthWest(Tile* tile){
        return &Matrix[tile->y-1][tile->x-1];
    } 