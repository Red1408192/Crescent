#pragma once
#include "Tile.hpp"
#include "Cluster.hpp"
#include <vector>

class Map{
public:
    Map(int width, int height, int continents, int maxWeight = 200, int seed = 0);
    int Height;
    int Width;
    Tile& GetTile(int x, int y);
    bool IsValidPosition(int x, int y);
    std::vector<std::vector<Tile>> Matrix;
    std::vector<Cluster> Continents;

    Cluster& EvaluateCluster(Tile* tile);
    int FindShortestPath(Tile *start, Tile *end);
    int FindShortestPath(Tile *start, int endX, int endY);
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
