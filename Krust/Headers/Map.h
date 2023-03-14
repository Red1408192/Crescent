#pragma once
#include "Tile.h"
#include "Cluster.h"
#include <vector>

class Map{
    Map::Map(int width, int height, int maxWeight = 100, int minWeight = 0, int seed = 0);
    int* Height;
    int* Width;
public:
    Tile& GetTile(int x, int y);
    Cluster& EvaluateCluster(Tile* tile);
    std::vector<std::vector<Tile>> Matrix;
    std::vector<Cluster> Continents;

private:
};
