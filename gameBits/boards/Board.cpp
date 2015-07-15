//
// Created by Celito on 2015-06-27.
//

#include <algorithm>
#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "../../Game.h"

vector < shared_ptr<Tile> > Board::get_available_titles() {
    vector< shared_ptr<Tile> > ret;
    for_each(_tile_grid.begin(), _tile_grid.end(), [&ret](pair< TilePos, shared_ptr<Tile> > tile_entry){
        if(tile_entry.second->is_empty()){
            ret.push_back(tile_entry.second);
        }
    });
    return ret;
}

void Board::add_new_tile(TilePos pos) {
    if(_tile_grid[pos] != nullptr) return;
    shared_ptr<Tile> tile = make_shared<Tile>(*this, pos, _default_directions);
    _tile_grid[pos] = tile;
    _game.register_new_bit(tile);
    receive(tile);
    tile->on_piece_received( [](Tile &caller) {
        caller.populate_neighbours();
    });
}
