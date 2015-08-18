//
// Created by Celito on 7/9/2015.
//

#include "BitOption.h"
#include "../../../gameBits/GameBit.h"

BitOption::BitOption(shared_ptr<GameBit> game_bit)  : _selected_bit(game_bit) {}

string BitOption::get_description() {
    return _selected_bit->get_bit_name();
}

shared_ptr<GameBit> BitOption::get_bit() {
    return _selected_bit;
}


