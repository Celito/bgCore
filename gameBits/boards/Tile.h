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

    void update_neighbourhood();

    void populate_neighbours();

    virtual void receive(shared_ptr<GameBit> bit) override;

    TilePos const & get_pos() const { return  _pos; }

    int32_t x() const { return _pos.x(); }
    int32_t y() const { return _pos.y(); }

    bool is_updating() const { return _updating; }

    boost::signals2::connection on_piece_received(boost::signals2::slot<void(Tile &)> slot) {
        return _piece_received.connect(slot);
    }

private:
    vector< shared_ptr<Tile> > _neighbours;
    Board &_board;
    TilePos _pos;

    vector< TilePos > _directions;
    bool _updating;

    boost::signals2::signal<void(Tile &)> _piece_received;
};


#endif //BGCORE_TILE_H
