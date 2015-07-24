//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_BOARD_H
#define BGCORE_BOARD_H


#include "../GameBit.h"
#include "../BitHolder.h"
#include "TilePos.h"
#include "../Piece.h"
#include "../../player/Player.h"
#include <map>

class Tile;

using namespace std;

enum available_tiles_t {
    e_for_placement,
    e_for_movement
};

class Board : public GameBit, public BitHolder{
public:
    Board(Game &game, const string &bit_id) : GameBit(game, bit_id) { }

    vector<shared_ptr<Tile> > get_available_titles(available_tiles_t reason);

    vector< shared_ptr<Tile> > get_tiles();

    vector< shared_ptr<Piece> > get_available_pieces(shared_ptr<Player> player);

    vector< shared_ptr<Piece> > get_pieces();

    shared_ptr<Tile> get_tile(TilePos pos) const { return _tile_grid.count(pos) ? _tile_grid.at(pos) : nullptr; }

    void add_new_tile(TilePos pos);

    void remove_tile(TilePos pos);

protected:
    map< TilePos, shared_ptr< Tile > > _tile_grid;

    vector<TilePos> _default_directions;
};


#endif //BGCORE_BOARD_H
