//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_HEXBOARD_H
#define BGCORE_HEXBOARD_H


#include "../GameBit.h"
#include "../../Game.h"

class HexBoard : public GameBit {
public:
    HexBoard(Game &game, std::string refId);
};


#endif //BGCORE_HEXBOARD_H
