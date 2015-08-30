//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_HEXBOARD_H
#define BGCORE_HEXBOARD_H


#include "../GameBit.h"
#include "../../BgCore.h"
#include "Board.h"

class HexBoard : public Board {
public:
    HexBoard(BgCore &game, std::string refId);
};


#endif //BGCORE_HEXBOARD_H
