//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_BOARD_H
#define BGCORE_BOARD_H


#include "../GameBit.h"
#include "../BitHolder.h"
#include "TilePos.h"
#include "../Piece.h"
#include <map>

class Tile;

using namespace std;

class Board : public GameBit, public BitHolder{
public:
    Board(Game &game, const string &bit_id) : GameBit(game, bit_id) { }

    virtual bool have_free_tiles() = 0;

    vector< shared_ptr<Tile> > get_available_titles();

    vector< shared_ptr<Tile> > get_tiles();

    vector< shared_ptr<Piece> > get_pieces();

    shared_ptr<Tile> get_tile(TilePos pos) const { return _tile_grid.count(pos) ? _tile_grid.at(pos) : nullptr; }

    void add_new_tile(TilePos pos);

protected:
    map< TilePos, shared_ptr< Tile > > _tile_grid;

    vector<TilePos> _default_directions;
};


#endif //BGCORE_BOARD_H
