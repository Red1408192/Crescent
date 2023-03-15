#pragma once

struct Tile{
    Tile(int xPos, int yPos, unsigned int weight, unsigned int height);
    Tile();
    int x;
    int y;

    unsigned int Weight;
    unsigned int Height;
};
