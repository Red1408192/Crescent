#include "Headers/Map.hpp"
#include "Cluster.cpp"
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
    Continents(continents),
    Seed(seed)
    {
        srand(seed);
        int currentContinentIndex = 0;

        for (size_t i = 0; i < continents; i++)
        {
            bool terrestial = rand()%2==0;

            FastNoiseLite noise(Seed+i);
            noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
            noise.SetFrequency(0.018f);
            noise.SetFractalType(FastNoiseLite::FractalType_FBm);
            noise.SetFractalOctaves(6);
            noise.SetFractalLacunarity(2.6f);
            noise.SetFractalGain(0.5f);
            Continents[i] = Cluster(i,(rand()+10)%(height-10), (rand()+10)%(height-10), noise, terrestial);
        }
        FastNoiseLite noise(Seed);
        noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
        noise.SetFrequency(0.018f);
        noise.SetFractalType(FastNoiseLite::FractalType_FBm);
        noise.SetFractalOctaves(6);
        noise.SetFractalLacunarity(2.6f);
        noise.SetFractalGain(0.5f);
        for (size_t y = 0; y < height; y++)
        {
            for (size_t x = 0; x < width; x++)
            {

                Matrix[y][x] = Tile(x, y, 50.*(1.5+noise.GetNoise((float)x, (float)y))/2);
                int currentShortestIndex = 21;
                int currentSSecondIndex = 21;

                int currentShortest = __INT_MAX__;
                int currentSecondShortest = __INT_MAX__;

                for (size_t i = 0; i < continents; i++){
                    auto h = Continents[i].FindShortestPath(Matrix[y][x], width);

                    if(currentShortest > h){
                        currentSSecondIndex = currentShortestIndex;
                        currentShortestIndex = i;
                        currentSecondShortest = currentShortest;
                        currentShortest = h;
                    }
                }
                if(Continents[currentContinentIndex].Terrestial) Matrix[y][x].Height *= 20;
                if(Continents[currentContinentIndex].Terrestial && Continents[currentSecondShortest].Terrestial){
                    auto delta = currentSecondShortest - currentShortest;
                    auto heightFactor = (((log10(delta)+1.)/3.)+.3)*2;
                    Matrix[y][x].Height *= heightFactor;
                }
                else{
                    auto delta = currentSecondShortest - currentShortest;
                    auto heightFactor = (pow(delta, -3.)+1.);
                    Matrix[y][x].Height *= heightFactor;
                }
                Matrix[y][x].ClusterIndex = currentShortestIndex;
            }
        }
    };
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

