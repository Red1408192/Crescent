#pragma once
#include "Tile.hpp"
#include "Cluster.hpp"
#include <vector>
#include "../FastNoiseLite.h"

class Map{
public:
    Map(int width, int height, int continents, int maxWeight = 200, int seed = 0);
    int Height;
    int Width;
    int Seed;
    Tile& GetTile(int x, int y);
    bool IsValidPosition(int x, int y);
    std::vector<std::vector<Tile>> Matrix;
    std::vector<Cluster> Continents;

    int FindShortestPath(Tile start, Tile end, FastNoiseLite noise);
    int FindShortestPath(Tile start, int endX, int endY, FastNoiseLite noise);
    Tile* GetNorth(Tile* tile);
    Tile* GetSouth(Tile* tile);
    Tile* GetEast(Tile* tile);
    Tile* GetWest(Tile* tile);
    Tile* GetNorthEast(Tile* tile);
    Tile* GetNorthWest(Tile* tile);
    Tile* GetSouthEast(Tile* tile);
    Tile* GetSouthWest(Tile* tile);
private:
};
