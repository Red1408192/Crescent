#include "Headers/Map.hpp"
#include "Headers/Cluster.hpp"
#include "Tile.cpp"
#include <vector>
#include <cstddef>
#include <cstdlib>
#include <map>
#include <FastNoise/FastNoise.h>

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
            clusterCenters[i] = std::pair<int, int>(rand()%height, rand()%height);
        }

        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                Matrix[y][x] = Tile(x, y, (rand() % maxWeight), 1000);
                int currentShortestIndex = INT_MAX;
                int currentShortest = INT_MAX;
                for (size_t i = 0; i < continents; i++){
                    auto h = FindShortestPath(&Matrix[y][x], clusterCenters[i].first, clusterCenters[i].second);
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
        return static_cast<int>(start->GetDistance(end));
    }
    int Map::FindShortestPath(Tile *start, int endX, int endY){
        return static_cast<int>(start->GetDistance(endX, endY));
    }