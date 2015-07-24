//
// Created by Celito on 7/14/2015.
//

#ifndef BGCORE_TILE_H
#define BGCORE_TILE_H


#include <stdint-gcc.h>
#include <vector>
#include <memory>
#include <boost/signals2.hpp>
#include "../Piece.h"
#include "Board.h"
#include "TilePos.h"

using namespace std;

class Tile : public GameBit, public BitHolder {
public:
    Tile(Board &board, TilePos location, vector< TilePos > directions);

    void update_neighbourhood(shared_ptr<Tile> self);

    void populate_neighbours();

    void clear_neighbours();

    virtual void receive(shared_ptr<GameBit> bit) override;

    shared_ptr<Tile> get_neighbour(uint32_t dir) {
        return _neighbours[dir].expired()? nullptr : _neighbours[dir].lock();
    }

    void set_neighbour(uint32_t dir, shared_ptr<Tile> tile) {
        _neighbours[dir] = tile;
    }

    TilePos const & get_pos() const { return  _pos; }

    shared_ptr<Piece> get_top_piece() const;

    int32_t x() const { return _pos.x(); }
    int32_t y() const { return _pos.y(); }

    boost::signals2::connection on_piece_received(boost::signals2::slot<void(Tile &)> slot) {
        return _piece_received.connect(slot);
    }

    boost::signals2::connection on_piece_removed(boost::signals2::slot<void(Tile &, Piece &)> slot) {
        return _piece_removed.connect(slot);
    }

protected:
    virtual void remove(shared_ptr<GameBit> bit) override;

private:
    vector< weak_ptr<Tile> > _neighbours;
    Board &_board;
    TilePos _pos;

    vector< TilePos > _directions;
    bool _updating;

    boost::signals2::signal<void(Tile &)> _piece_received;
    boost::signals2::signal<void(Tile &, Piece &)> _piece_removed;
};


#endif //BGCORE_TILE_H
