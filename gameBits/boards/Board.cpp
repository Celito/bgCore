//
// Created by Celito on 2015-06-27.
//

#include <algorithm>
#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "../../BgCore.h"
#include "../../BitsManager.h"
#include "../../turns/State.h"

void Board::add_new_tile(TilePos pos) {
    if(_tile_grid[pos] != nullptr) return;
    shared_ptr<Tile> tile = make_shared<Tile>(*this, pos, _default_directions);
    _tile_grid[pos] = tile;
    _game.register_new_bit(tile);
    receive(tile);
    if(_grown_on_usage){
        tile->on_piece_received( [](Tile &caller) {
            caller.populate_neighbours();
        });
    }
}

vector< shared_ptr<Tile> > Board::get_tiles() {
    vector< shared_ptr<Tile> > ret;
    for_each(_tile_grid.begin(), _tile_grid.end(), [&ret](pair< TilePos, shared_ptr<Tile> > tile_entry){
        ret.push_back(tile_entry.second);
    });
    return ret;
}

vector< shared_ptr<Piece> > Board::get_pieces() {
    vector< shared_ptr<Tile> > tiles = get_tiles();
    vector< shared_ptr<Piece> > ret;
    for_each(tiles.begin(), tiles.end(), [&ret]( shared_ptr<Tile> tile){
        if(!tile->is_empty())
            ret.push_back(tile->get_top_piece());
    });
    return ret;
}

void Board::remove_tile(TilePos pos) {
    if(_tile_grid.count(pos) < 1) return;
    shared_ptr<Tile> tile = _tile_grid[pos];
    remove(tile);
    _game.bits_manager()->remove_bit(tile);

    _tile_grid.erase(pos);

}

void Board::initialize_tiles(bool grown_on_usage) {
    _grown_on_usage = grown_on_usage;
    auto zero = TilePos(0, 0);
    add_new_tile(zero);
}
