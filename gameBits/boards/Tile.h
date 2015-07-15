//
// Created by Celito on 7/14/2015.
//

#ifndef BGCORE_TILE_H
#define BGCORE_TILE_H


#include <stdint-gcc.h>
#include <vector>
#include <memory>
#include "../Piece.h"
#include "Board.h"
#include "TilePos.h"

using namespace std;

class Tile : public GameBit, public BitHolder {
public:
    Tile(Board &board, TilePos location, vector< TilePos > const &directions);

    void update_neighbourhood();

    TilePos const & get_pos() const { return  _pos; }

    int32_t x() const { return _pos.x(); }
    int32_t y() const { return _pos.y(); }

    bool is_updating() const { return _updating; }

private:
    vector< weak_ptr<Tile> > _neighbours;
    Board &_board;
    TilePos _pos;

    vector< TilePos > const &_directions;
    bool _updating;
};


#endif //BGCORE_TILE_H
