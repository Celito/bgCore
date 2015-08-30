//
// Created by Celito on 7/14/2015.
//

#ifndef BGCORE_TILE_H
#define BGCORE_TILE_H


#include <stdint.h>
#include <vector>
#include <memory>
#include <boost/signals2.hpp>
#include "../GameBit.h"
#include "TilePos.h"

class Piece;
class Board;

using namespace std;

class Tile : public GameBit {
public:
    Tile(Board &board, TilePos location, vector< TilePos > directions);

    void populate_neighbours();

    virtual void receive(shared_ptr<GameBit> bit) override;

	shared_ptr<Tile> get_neighbour(uint32_t dir);

    uint32_t get_num_of_directions(){
        return _directions.size();
    }

    TilePos const & get_pos() const { return  _pos; }

    shared_ptr<Piece> get_top_piece() const;

    int32_t x() const { return _pos.x(); }
    int32_t y() const { return _pos.y(); }

    uint32_t get_direction_of(TilePos neighbour_pos);

    boost::signals2::connection on_piece_received(boost::signals2::slot<void(Tile &)> slot) {
        return _piece_received.connect(slot);
    }

protected:
    virtual void remove(shared_ptr<GameBit> bit) override;

private:
    Board &_board;
    TilePos _pos;

    vector< TilePos > _directions;
    bool _updating;

    boost::signals2::signal<void(Tile &)> _piece_received;
    boost::signals2::signal<void(Tile &, Piece &)> _piece_removed;
};


#endif //BGCORE_TILE_H
