#include "Headers/Map.h"
#include "Headers/Cluster.h"
#include "Tile.cpp"
#include <vector>
#include <cstddef>
#include <cstdlib>

Map::Map(int width, int height, int continents, int maxWeight, int seed):
    Matrix(height, std::vector<Tile>(width)),
    Height(height),
    Width(width),
    Continents(continents)
    {
        srand(seed);        
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {
                Matrix[y][x] = Tile(x, y, (rand() % maxWeight), 1000);
            }
        }
        for (size_t i = 0; i < 7; i++)
        {
            Continents[i].CenterTile = &Matrix[rand()%height][rand()%height];
        }
        
    };