//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_BOARD_H
#define BGCORE_BOARD_H


#include "../GameBit.h"

class Board : public GameBit, public BitHolder{
public:
    Board(Game &game, const string &bit_id) : GameBit(game, bit_id) { }

    virtual bool have_free_tiles() = 0;
};


#endif //BGCORE_BOARD_H
