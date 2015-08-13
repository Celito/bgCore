//
// Created by Celito on 8/13/2015.
//

#include "IsEmpty.h"
#include "../gameBits/boards/Tile.h"

bool IsEmpty::test() {
    if(_required_bits.count(e_tile) == 0) throw new exception();
    if(_required_bits[e_tile].expired()) throw new exception();
    shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(_required_bits[e_tile].lock());

    return tile->is_empty();
}