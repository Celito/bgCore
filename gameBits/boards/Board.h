//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_BOARD_H
#define BGCORE_BOARD_H


#include "../GameBit.h"
#include "TilePos.h"
#include <map>

class Tile;
class Piece;
class Player;
class Option;

using namespace std;

enum available_tiles_t {
    e_for_placement,
    e_for_movement
};

class Board : public GameBit{
public:
    Board(BgCore &game, const string &bit_id) : GameBit(game, bit_id) { }

    virtual void initialize_tiles(bool grown_on_usage);

    vector< shared_ptr<Tile> > get_tiles();

    vector< shared_ptr<Piece> > get_pieces();

    shared_ptr<Tile> get_tile(TilePos pos) const { return _tile_grid.count(pos) ? _tile_grid.at(pos) : nullptr; }

    void add_new_tile(TilePos pos);

    void remove_tile(TilePos pos);

    boost::signals2::connection on_tile_added(boost::signals2::slot<void(const shared_ptr<Tile> &)> slot);

protected:
    map< TilePos, shared_ptr< Tile > > _tile_grid;

    vector<TilePos> _default_directions;

    boost::signals2::signal<void(const shared_ptr<Tile> &)> _tile_added;

    bool _grown_on_usage = false;
};


#endif //BGCORE_BOARD_H
