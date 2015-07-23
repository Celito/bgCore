//
// Created by Celito on 2015-05-29.
//

#include <c++/iostream>
#include <algorithm>
#include "HexBoard.h"
#include "../../BitsManager.h"

using namespace std;

HexBoard::HexBoard(Game &game, string refId) : Board(game, refId){
    auto zero = TilePos(0, 0);
    _default_directions =
            {TilePos(0, 2), TilePos(1, 1), TilePos(1, -1), TilePos(0, -2), TilePos(-1, -1), TilePos(-1, 1)};
    add_new_tile(zero);
}
