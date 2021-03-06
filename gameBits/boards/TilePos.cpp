//
// Created by Celito on 7/14/2015.
//

#include "TilePos.h"

TilePos TilePos::operator+(const TilePos &pos) const {
    return TilePos(first + pos.first, second + pos.second);
}

TilePos::TilePos(int32_t x, int32_t y) : pair<int32_t, int32_t>(x, y) {}

string TilePos::to_string() const {
    return string("[ ") + std::to_string(x()) + ", " + std::to_string(y()) + " ]";
}

TilePos TilePos::operator-(TilePos const &pos) const {
    return TilePos(first - pos.first, second - pos.second);
}
