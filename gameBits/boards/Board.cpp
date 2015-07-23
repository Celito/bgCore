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

vector<shared_ptr<Tile> > Board::get_tiles() {
    vector< shared_ptr<Tile> > ret;
    for_each(_tile_grid.begin(), _tile_grid.end(), [&ret](pair< TilePos, shared_ptr<Tile> > tile_entry){
        ret.push_back(tile_entry.second);
    });
    return ret;
}

vector<shared_ptr<Piece> > Board::get_pieces() {
    vector< shared_ptr<Tile> > tiles = get_tiles();
    vector< shared_ptr<Piece> > ret;
    for_each(tiles.begin(), tiles.end(), [&ret]( shared_ptr<Tile> tile){
        if(!tile->is_empty())
            ret.push_back(tile->get_top_piece());
    });
    return ret;
}

vector<shared_ptr<Piece> > Board::get_available_pieces(shared_ptr<Player> player) {
    vector< shared_ptr<Tile> > tiles = get_tiles();
    vector< shared_ptr<Piece> > ret;
    for_each(tiles.begin(), tiles.end(), [&ret, &player]( shared_ptr<Tile> tile){
        shared_ptr<Piece> piece = tile->get_top_piece();
        if(piece != nullptr && piece->available_for_movement(player))
        {
            ret.push_back(piece);
        }

    });
    return ret;
}
