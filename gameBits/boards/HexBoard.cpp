//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
#include <algorithm>
#include "HexBoard.h"
#include "Tile.h"
#include "../../BitsManager.h"

using namespace std;

HexBoard::HexBoard(Game &game, string refId) : Board(game, refId){
    auto zero = TilePos(0, 0);
    _default_directions =
            {TilePos(0, 2), TilePos(1, 1), TilePos(1, -1), TilePos(0, -2), TilePos(-1, -1), TilePos(-1, 1)};
    add_new_tile(zero);
}

bool HexBoard::have_free_tiles() {
    //TODO: Make this function to be restricted by the rules of placement of the piece
    bool ret = false;
    for_each(_tile_grid.begin(), _tile_grid.end(), [&ret](pair< TilePos, shared_ptr<Tile> > grid_entry){
        ret |= grid_entry.second->is_empty();
    });
    return ret;
}
