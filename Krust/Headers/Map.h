#pragma once
#include "Tile.h"
#include "Cluster.h"
#include <vector>

class Map{
public:
    Map(int width, int height, int continents, int maxWeight = 200, int seed = 0);
    int Height;
    int Width;
    Tile& GetTile(int x, int y);
    Cluster& EvaluateCluster(Tile* tile);
    bool IsValidPosition(int x, int y);
    std::vector<std::vector<Tile>> Matrix;
    std::vector<Cluster> Continents;
private:
};
