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
