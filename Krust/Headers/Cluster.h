#pragma once
#include <vector>
#include "Tile.h"

class Cluster{
    private:
        Tile center;

    public:
        int Identifier;
        void AddTile(Tile& tile);
        std::vector<Tile*> MemberTiles;
};