//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
#include "HexBoard.h"
#include "Tile.h"

using namespace std;

HexBoard::HexBoard(Game &game, string refId) : Board(game, refId){
    auto zero = TilePos(0, 0);
    _directions = {TilePos(0, 2), TilePos(1, 1), TilePos(1, -1), TilePos(0, -2), TilePos(-1, -1), TilePos(-1, 1)};
    _tile_grid[zero] = make_shared<Tile>(*this, zero, _directions);
}

bool HexBoard::have_free_tiles() {
    //TODO: Complete this function;
    return true;
}
