//
// Created by Celito on 7/14/2015.
//

#include "TilePos.h"

TilePos TilePos::operator+(const TilePos &pos) const {
    return TilePos(pos.first + first, pos.second + second);
}

TilePos::TilePos(int32_t x, int32_t y) : pair<int32_t, int32_t>(x, y) {}

