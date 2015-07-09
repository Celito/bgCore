//
// Created by Celito on 7/9/2015.
//

#ifndef BGCORE_BITOPTION_H
#define BGCORE_BITOPTION_H

#include "Option.h"

class GameBit;

class BitOption : public Option {
public:
    BitOption(shared_ptr<GameBit> game_bit) : _selected_bit(game_bit) {}

    virtual string get_description() override;

private:
    shared_ptr<GameBit> _selected_bit;
};


#endif //BGCORE_BITOPTION_H
