//
// Created by Celito on 2015-05-29.
//

#include <iostream>
#include <algorithm>
#include "HexBoard.h"
#include "../../BitsManager.h"

using namespace std;

HexBoard::HexBoard(BgCore &game, string refId) : Board(game, refId){
    _default_directions =
            {TilePos(0, 2), TilePos(1, 1), TilePos(1, -1), TilePos(0, -2), TilePos(-1, -1), TilePos(-1, 1)};
}
