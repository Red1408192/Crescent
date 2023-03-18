#pragma once
#include <vector>
#include "Tile.hpp"

class Cluster{
    private:
    public:
        int Identifier;
        std::vector<Tile*> MemberTiles;
        Tile* CenterTile;
};