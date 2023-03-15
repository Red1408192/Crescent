#pragma once
#include <vector>
#include "Tile.h"

class Cluster{
    private:
    public:
        int Identifier;
        std::vector<Tile*> MemberTiles;
        Tile* CenterTile;
};