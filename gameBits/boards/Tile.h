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

class Tile {
public:
    Tile(Board &board, TilePos location, vector< TilePos > const &directions);

    void update_neighbourhood();

    int32_t x() { return _location.first; }
    int32_t y() { return _location.second; }

    void put_piece(shared_ptr<Piece> piece);

    bool is_empty();

    bool is_updating() { return _updating; }

private:
    vector< weak_ptr<Tile> > _neighbours;
    Board &_board;
    vector< shared_ptr<Piece> > _pieces_stack;
    TilePos _location;

    vector< TilePos > const &_directions;
    bool _updating;
};


#endif //BGCORE_TILE_H
